#include "PluginManager.hpp" // IWYU pragma: associated

#include "ServerPlugin.hpp"

#include <Corrade/PluginManager/Manager.h>
#include <Corrade/PluginManager/PluginMetadata.h>
#include <Corrade/Utility/Arguments.h>
#include <Corrade/Utility/Configuration.h>
#include <Corrade/Utility/ConfigurationGroup.h>
#include <Corrade/Utility/Debug.h>
#include <Corrade/Utility/DebugStl.h>
#include <Corrade/Utility/Directory.h>
#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Pointer.h>

#include <base/logging.h>
#include <base/trace_event/trace_event.h>
#include <base/files/file.h>
#include <base/files/file_path.h>
#include <base/files/file_enumerator.h>
#include <base/files/file_util.h>

namespace backend {

void PluginManager::connect_to_dispatcher(entt::dispatcher& events_dispatcher)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  TRACE_EVENT0("toplevel", "PluginManager::connect_to_dispatcher()");

  events_dispatcher.sink<Events::Startup>()
      .connect<&PluginManager::startup>(this);
  events_dispatcher.sink<Events::Shutdown>()
      .connect<&PluginManager::shutdown>(this);
}

void PluginManager::connect_plugins_to_dispatcher(
  entt::dispatcher& events_dispatcher)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  TRACE_EVENT0("toplevel", "PluginManager::connect_to_dispatcher()");

  for(PluginPtr& loaded_plugin : loaded_plugins_) {
    DCHECK(loaded_plugin);
    loaded_plugin->connect_to_dispatcher(events_dispatcher);
  }
}

void PluginManager::startup(const Events::Startup& event)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  TRACE_EVENT0("toplevel", "PluginManager::startup()");

  LOG(INFO) << "(PluginManager) startup";

  const std::string executable_path
    = ::Corrade::Utility::Directory::path(
        ::Corrade::Utility::Directory::executableLocation());

  const std::string plugins_conf_path
    = ::Corrade::Utility::Directory::join(
        std::initializer_list<std::string>{executable_path
        , "assets"
        , "configuration_files"
        , "plugins.conf"}
      );

  DLOG(INFO)
    << "using plugins configuration file "
    << plugins_conf_path;

  Corrade::Utility::Configuration conf{plugins_conf_path};
  std::vector<Corrade::Utility::ConfigurationGroup*> plugin_groups;
  bool plugin_filtering_enabled = false;
  if(conf.hasGroups()) {
    if(conf.hasGroup("plugins")) {
      plugin_filtering_enabled = true;
      Corrade::Utility::ConfigurationGroup* configurationGroup
        = conf.group("plugins");
      if(configurationGroup) {
        plugin_groups = configurationGroup->groups("plugin");
      }
    }
  }

  manager_
    = std::make_unique<
        ::Corrade::PluginManager::Manager<
          PluginType
        >
      >();

  // Initialize plugin manager with given directory
  // see https://doc.magnum.graphics/corrade/classCorrade_1_1PluginManager_1_1Manager.html
  const std::string plugins_dir_path
    = ::Corrade::Utility::Directory::join(
        executable_path
        , "plugins"
      );

  // Set the plugin manager to load plugins from same directory as this app
  manager_->setPluginDirectory(plugins_dir_path);

  DLOG(INFO)
    << "Using plugin directory:"
    << manager_->pluginDirectory();

  std::vector<std::string> all_plugins
    = manager_->pluginList();

  std::vector<std::string> filtered_plugins;

  if(plugin_filtering_enabled)
  {
    //if(plugin_groups.empty()) {
    //  filtered_plugins.clear();
    //}

    bool is_allowed = false;
    for(const Corrade::Utility::ConfigurationGroup* plugin_group
        : plugin_groups)
    {
      if(!plugin_group->hasValue("title"))
      {
        LOG(WARNING)
          << "invalid plugin configuration: "
          << "title not provided";
        DCHECK(false);
        continue;
      }

      const std::string plugin_conf_name
        = plugin_group->value("title");
      auto find_result
        = std::find(all_plugins.begin()
            , all_plugins.end()
            , plugin_conf_name);
      if(find_result == all_plugins.end())
      {
        LOG(WARNING)
          << "plugin not found: "
          << plugin_conf_name;
        /// \note will crash in production!
        CHECK(false);
      } else {
        filtered_plugins.push_back(plugin_conf_name);
      }
    }
  }

  for(std::vector<std::string>::const_iterator it = filtered_plugins.begin()
      ; it != filtered_plugins.end(); ++it)
  {
    const std::string& plugin_name = *it;

    LOG(INFO)
      << "plugin enabled: "
      << plugin_name;

    const bool is_loaded
      = static_cast<bool>(manager_->load(plugin_name)
        & (Corrade::PluginManager::LoadState::Loaded
           | Corrade::PluginManager::LoadState::Static)
        );
    if(!is_loaded) {
        LOG(ERROR)
          << "The requested plugin "
          << plugin_name
          << " cannot be loaded.";
        DCHECK(false);
        continue;
    }

    /// \note The plugin must be already
    /// successfully loaded by this manager.
    /// \note The returned value is never |nullptr|
    PluginPtr plugin
      = manager_->instantiate(plugin_name);
    if(!plugin) {
      LOG(ERROR)
        << "The requested plugin "
        << plugin_name
        << " cannot be instantiated.";
      DCHECK(false);
      continue;
    }

    LOG(INFO)
      << "=== loading plugin ==";
    LOG(INFO)
      << "plugin title:       "
      << plugin->title();
    LOG(INFO)
      << "plugin description: "
      << plugin->description().substr(0, 100)
      << "...";

    plugin->load();

    loaded_plugins_.push_back(std::move(plugin));
    LOG(INFO)
      << "=== plugin loaded ==";
  }

  is_initialized_ = true;
}

void PluginManager::shutdown(const Events::Shutdown& event)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  TRACE_EVENT0("toplevel", "PluginManager::shutdown()");

  LOG(INFO) << "(PluginManager) shutdown";

  /// \note destructor of ::Corrade::PluginManager::Manager
  /// also unloads all plugins
  for(PluginPtr& loaded_plugin : loaded_plugins_) {
    DCHECK(loaded_plugin);
    loaded_plugin->unload();
    //loaded_plugin.reset(nullptr);
  }
}

} // namespace backend
