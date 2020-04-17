#pragma once

#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>
#include <entt/entity/helper.hpp>
#include <entt/entity/group.hpp>

#include <base/macros.h>
#include <base/sequenced_task_runner.h>
#include <base/trace_event/trace_event.h>

#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Containers/Pointer.h>

namespace plugin {

class ServerPlugin;

} // namespace plugin

/// \todo hide impl details
//namespace Corrade {
//
//namespace PluginManager {
//
//template<class T>
//class Manager;
//
//} // namespace Corrade
//
//} // namespace Corrade

namespace backend {

class PluginManager {
public:
  typedef ::plugin::ServerPlugin PluginType;
  typedef Corrade::Containers::Pointer<
            PluginType
          > PluginPtr;

  struct Events {
    struct Startup {
      std::string pluginsFullDir;
    };
    struct Shutdown {
      // event parameters
    };
    struct ConsoleCmd {
      std::string cmd;
    };
  };

public:
  PluginManager()
  {
    DETACH_FROM_SEQUENCE(sequence_checker_);
  }

  ~PluginManager() {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

    /// \note destoy |entt::dispatcher| before plugin manager
  }

  // |dispatcher| to handle per-plugin events
  void connect_plugins_to_dispatcher(
    entt::dispatcher& events_dispatcher);

  // |dispatcher| to handle |PluginManager|
  // events like |Startup| or |Shutdown|
  void connect_to_dispatcher(
    entt::dispatcher& events_dispatcher);

  void startup(
    const Events::Startup& event);

  void shutdown(
    const Events::Shutdown& event);

  size_t countLoadedPlugins()
    const noexcept
  {
    return loaded_plugins_.size();
  }

private:
  bool is_initialized_ = false;

  std::unique_ptr<
    ::Corrade::PluginManager::Manager<PluginType>
    > manager_;

  std::vector<PluginPtr> loaded_plugins_;

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(PluginManager);
};

} // namespace backend
