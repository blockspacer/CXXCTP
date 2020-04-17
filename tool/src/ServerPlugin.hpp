#pragma once

#include "common/ECS/EnttManager.hpp"

#include <string>
#include <vector>
#include <Corrade/PluginManager/AbstractPlugin.h>
#include <Corrade/PluginManager/AbstractManager.h>
#include <Corrade/PluginManager/PluginManager.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/PluginManager/PluginMetadata.h>
#include <Corrade/Utility/Arguments.h>
#include <Corrade/Utility/ConfigurationGroup.h>
#include <Corrade/Utility/Debug.h>
#include <Corrade/Utility/DebugStl.h>
#include <Corrade/Utility/Directory.h>
#include <Corrade/Containers/Array.h>

#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>
#include <entt/entity/helper.hpp>
#include <entt/entity/group.hpp>

#include <base/logging.h>
#include <base/cpu.h>
#include <base/command_line.h>
#include <base/debug/alias.h>
#include <base/debug/stack_trace.h>
#include <base/debug/thread_heap_usage_tracker.h>
#include <base/memory/ptr_util.h>
#include <base/sequenced_task_runner.h>
#include <base/strings/string_util.h>
#include <base/trace_event/trace_event.h>

#define REGISTER_PLUGIN(name, className, interface) \
  CORRADE_PLUGIN_REGISTER(name, className, interface)

namespace plugin {

typedef ::Corrade::PluginManager::AbstractManager AbstractManager;
typedef ::Corrade::PluginManager::AbstractPlugin AbstractPlugin;

class ServerPlugin
  : public ::plugin::AbstractPlugin
{
 public:
  struct Events {
    struct ConsoleCmd {
      // unprocessed command
      std::string raw_cmd;

      // |raw_cmd| split by space
      std::vector<std::string> split_parts;
    };

    struct SimulationCreated {
      // wrapper around |entt::registry|
      ECS::EnttManager* enttManager = nullptr;
    };

    struct ArbitraryRemoteData {
      uint8_t* data;

      std::uint32_t command_id = 0;

      uint32_t data_size= 0;
    };

  };

  explicit ServerPlugin(
    ::plugin::AbstractManager& manager
    , const std::string& plugin)
    : AbstractPlugin{manager, plugin}
  {
    DETACH_FROM_SEQUENCE(sequence_checker_);
  }

  static std::string pluginInterface() {
    // plugin interface version checks to avoid unexpected behavior
    return "backend.ServerPlugin/1.0";
  }

  static std::vector<std::string> pluginSearchPaths() {
    return {""};
  }

  virtual void connect_to_dispatcher(
    entt::dispatcher& event_dispatcher) = 0;

  virtual void disconnect_dispatcher(
    entt::dispatcher& event_dispatcher) = 0;

  //virtual void handle_event_ConsoleCmd(
  //  const ::plugin::ServerPlugin::Events::ConsoleCmd& event) = 0;
  //
  //virtual void handle_event_SimulationCreated(
  //  const ::plugin::ServerPlugin::Events::SimulationCreated& event) = 0;

  virtual std::string author() const = 0;

  virtual std::string title() const = 0;

  virtual std::string description() const = 0;

  virtual bool load() = 0;

  virtual bool unload() = 0;

protected:
  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(ServerPlugin);
};

} // namespace plugin
