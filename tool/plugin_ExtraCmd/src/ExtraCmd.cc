#include <ServerPlugin.hpp>

#include <base/logging.h>
#include <base/cpu.h>
#include <base/bind.h>
#include <base/command_line.h>
#include <base/debug/alias.h>
#include <base/debug/stack_trace.h>
#include <base/debug/thread_heap_usage_tracker.h>
#include <base/memory/ptr_util.h>
#include <base/sequenced_task_runner.h>
#include <base/strings/string_util.h>
#include <base/trace_event/trace_event.h>

#include <Poco/ByteOrder.h>
#include <Poco/Platform.h>
#include <Poco/Environment.h>
#include <Poco/Format.h>
#include <Poco/DateTime.h>
#include <Poco/Timezone.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Stopwatch.h>
#include <Poco/String.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/Statement.h>
#include <Poco/Exception.h>
#include <Poco/Timespan.h>

#include <common/ECS/singletons/AppRunningFlag.hpp>
#include <common/ECS/singletons/ConsoleCmdQueue.hpp>

#include "generated/flatbuffers/RemoteMessage_generated.h"

static const std::string kPluginDebugLogName = "(ExtraCmd plugin)";

static const std::string kVersion = "v0.0.1";

static const std::string kVersionCommand = "/version";

static const std::string kShutdownCommand = "/shutdown";

static const size_t kRemoteCommandId = 101;

#if !defined(APPLICATION_BUILD_TYPE)
#define APPLICATION_BUILD_TYPE "local build"
#endif

namespace {

static bool warnIfNoRegistry(ECS::EnttManager* enttManager)
{
  if(!enttManager) {
    LOG(WARNING)
      << kPluginDebugLogName
      << " unable to handle command:"
         " registry not created!";
    return true;
  }
  return false;
}

} // namespace

namespace plugin {

class ExtraCmd
  final
  : public ::plugin::ServerPlugin {
 public:
  explicit ExtraCmd(
    ::plugin::AbstractManager& manager
    , const std::string& plugin)
    : ::plugin::ServerPlugin{manager, plugin}
  {
    DETACH_FROM_SEQUENCE(sequence_checker_);
  }

  std::string title() const override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

    return metadata()->data().value("title");
  }

  std::string author() const override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

    return metadata()->data().value("author");
  }

  std::string description() const override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

    return metadata()->data().value("description");
  }

  bool load() override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    TRACE_EVENT0("toplevel", "plugin::ExtraCmd::load()");

    DLOG(INFO)
      << "loaded plugin with title = "
      << title()
      << " and description = "
      << description().substr(0, 100)
      << "...";

    return true;
  }

  void disconnect_dispatcher(
    entt::dispatcher &event_dispatcher) override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    TRACE_EVENT0("toplevel", "plugin::ExtraCmd::connect_to_dispatcher()");

    event_dispatcher.sink<::plugin::ServerPlugin::Events::ConsoleCmd>()
        .disconnect<&ExtraCmd::handle_event_ConsoleCmd>(this);

    event_dispatcher.sink<::plugin::ServerPlugin::Events::SimulationCreated>()
        .disconnect<&ExtraCmd::handle_event_SimulationCreated>(this);

    event_dispatcher.sink<::plugin::ServerPlugin::Events::ArbitraryRemoteData>()
        .disconnect<&ExtraCmd::handle_event_ArbitraryRemoteData>(this);
  }

  void connect_to_dispatcher(
    entt::dispatcher &event_dispatcher) override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    TRACE_EVENT0("toplevel", "plugin::ExtraCmd::connect_to_dispatcher()");

    event_dispatcher.sink<::plugin::ServerPlugin::Events::ConsoleCmd>()
        .connect<&ExtraCmd::handle_event_ConsoleCmd>(this);

    event_dispatcher.sink<::plugin::ServerPlugin::Events::SimulationCreated>()
        .connect<&ExtraCmd::handle_event_SimulationCreated>(this);

    event_dispatcher.sink<::plugin::ServerPlugin::Events::ArbitraryRemoteData>()
        .connect<&ExtraCmd::handle_event_ArbitraryRemoteData>(this);
  }

  void handle_event_ArbitraryRemoteData(
    const ::plugin::ServerPlugin::Events::ArbitraryRemoteData& event) //override
  {
    if(event.command_id != kRemoteCommandId) {
      DLOG(INFO)
        << kPluginDebugLogName
        << " skipping command id: "
        << event.command_id;
      return;
    }

    /// \note it is just pointer to array
    const uint8_t* data_start = event.data;

    const uint32_t& data_size = event.data_size;

    const auto parsed_buffer_ok = flatbuffers::Verifier(
        reinterpret_cast<const uint8_t*>(data_start),
        data_size
      ).VerifyBuffer<RemoteMessage::RemoteCmd>(nullptr);
    DCHECK(parsed_buffer_ok);
    const RemoteMessage::RemoteCmd* remoteCmd
      = flatbuffers::GetRoot<RemoteMessage::RemoteCmd>(
        reinterpret_cast<const uint8_t*>(data_start)
      );
    DCHECK(remoteCmd);

    const flatbuffers::String* command = remoteCmd->command();
    if(!command) {
      LOG(WARNING)
        << "something went wrong!";
      DCHECK(false);
    }

    if(command->str().empty() || command->size() > 99999) {
      LOG(WARNING) << "got wrong candidate description from client ="
        << command->str().substr(0, 100);
      return;
    }

    const flatbuffers::String* auth_token = remoteCmd->auth_token();
    if(!auth_token) {
      LOG(WARNING)
        << "something went wrong!";
      DCHECK(false);
    }

    if(auth_token->str().empty() || auth_token->size() > 99999) {
      LOG(WARNING) << "got wrong candidate description from client ="
        << auth_token->str().substr(0, 100);
      return;
    }

    if(warnIfNoRegistry(enttManager_)) {
      return;
    }

    enttManager_->async_post_task_on_sequence(base::BindOnce(
      []
      (const std::string full_command_copy
       , const std::string auth_token_copy
       , ECS::EnttManager* enttManager_ptr_copy)
      {
        if(warnIfNoRegistry(enttManager_ptr_copy)) {
          return;
        }

        /// \note write into queue from multiple threads
        ECS::ConsoleCmdQueue& console_cmd_queue
          = enttManager_ptr_copy->ctx<ECS::ConsoleCmdQueue>();

        if(auth_token_copy != "TODO") { /// \todo validate auth token
          LOG(WARNING)
            << "Unable to handle remote command: wrong auth token:"
            << auth_token_copy.substr(0, 100);
          return;
        }

        if (console_cmd_queue.commands.isFull()) {
          LOG(WARNING)
            << "Unable to handle remote command: full queue! command:"
            << full_command_copy.substr(0, 100);
          return;
        }

        // Emplace a value at the end of the queue, returns false if the queue was full.
        if (!console_cmd_queue.commands.write(full_command_copy)) {
          LOG(WARNING)
            << "Failed to add remote command: full queue! command: "
            << full_command_copy.substr(0, 100);
          return;
        }
      }
      , command->str()
      , auth_token->str()
      , enttManager_
    ));
  }

  void handle_event_SimulationCreated(
    const ::plugin::ServerPlugin::Events::SimulationCreated& event) //override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    TRACE_EVENT0("toplevel"
      , "plugin::ExtraCmd::handle_event(SimulationCreated)");

    DCHECK(event.enttManager);

    LOG(INFO)
      << kPluginDebugLogName
      << " simulation created";

    enttManager_ = event.enttManager;
  }

  void handle_event_ConsoleCmd(
    const ::plugin::ServerPlugin::Events::ConsoleCmd& event) //override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    TRACE_EVENT0("toplevel", "plugin::ExtraCmd::handle_event(ConsoleCmd)");

    if(event.split_parts.size() == 1)
    {
      if(event.split_parts[0] == kVersionCommand) {
        LOG(INFO)
          << kPluginDebugLogName
          << " application version: "
          << kVersion;
        LOG(INFO)
          << kPluginDebugLogName
          << " application build type: "
          << APPLICATION_BUILD_TYPE;
      }
      else if(event.split_parts[0] == kShutdownCommand) {
        if(warnIfNoRegistry(enttManager_)) {
          return;
        }
        LOG(INFO)
          << kPluginDebugLogName
          << " shutting down application";

        /// \note AppRunningFlag must be thread-safe
        ECS::AppRunningFlag& appRunningFlag
            = enttManager_->ctx_unsafe<ECS::AppRunningFlag>();

        appRunningFlag.is_app_running = false;
      }
    }
  }

  bool unload() override
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    TRACE_EVENT0("toplevel", "plugin::ExtraCmd::unload()");

    DLOG(INFO)
      << "unloaded plugin with title = "
      << title()
      << " and description = "
      << description().substr(0, 100)
      << "...";

    return true;
  }

private:
  ECS::EnttManager* enttManager_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(ExtraCmd);
};

} // namespace plugin

REGISTER_PLUGIN(/*name*/ ExtraCmd
    , /*className*/ plugin::ExtraCmd
    // plugin interface version checks to avoid unexpected behavior
    , /*interface*/ "backend.ServerPlugin/1.0")
