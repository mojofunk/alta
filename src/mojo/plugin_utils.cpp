#include <gmodule.h>

#include <map>

#include <mojo/plugin.hpp>
#include <mojo/file_utils.hpp>

#include <mojo/plugin_utils.hpp>

#include <iostream>

using namespace std;

typedef std::map<mojo::Plugin*, GModule*> PluginMap;

namespace {

PluginMap* plugin_map = 0;

void
_close_plugin (mojo::Plugin* plug)
{
	PluginMap::iterator i = plugin_map->find (plug);
	GModule* m = i->second;

	if (i == plugin_map->end()) return;

	// The plugin was allocated in a dynamically opened module
	// so the memory has to be deleted while the module is open.
	// and possibly from within the dll on windows?
	plugin_map->erase(i);
	delete plug;

	if (g_module_close (m) != TRUE)
	{
		cerr << "Unable to close module" << endl;
	}
}

mojo::PluginSPtr
_open_plugin (const std::string& plugin_path)
{
	GModule* module = NULL;
	mojo::plugin_func_t plugin_func = 0;

	module = g_module_open(plugin_path.c_str(), G_MODULE_BIND_LAZY);

	if (module == NULL)
	{
		cerr << "module == NULL:" << g_module_error() << endl;
		return mojo::PluginSPtr();
	} 

	if (g_module_symbol(module, "mojo_plugin_factory",
				(gpointer*)&plugin_func) == FALSE)
	{
		cerr << "Could not resolve symbol while opening plugin" << endl;
		return mojo::PluginSPtr();
	}

	if (plugin_func == NULL)
	{
		cerr << "factory_func == NULL" << endl;
		return mojo::PluginSPtr();
	}

	mojo::Plugin* p = static_cast<mojo::Plugin*>(plugin_func());

	mojo::PluginSPtr plug(p, _close_plugin);

	// XXX check
	plugin_map->insert (std::make_pair(p, module));

	return plug;
}

} // unnamed namespace

namespace mojo {

PluginSPtr
open_plugin (const fs::path& plugin_path)
{
	if (plugin_map == 0)
	{
		plugin_map = new PluginMap;
	}

	return _open_plugin(plugin_path.string());
}

bool
is_plugin_file (const fs::path& filepath)
{
	return (fs::extension (filepath) == "." G_MODULE_SUFFIX);
}

paths_t
get_plugin_paths (const paths_t& dirs)
{
	paths_t plugin_paths;

	find_matching_files (dirs, is_plugin_file, plugin_paths); 

	return plugin_paths;
}

plugins_t
discover_plugins (const SearchPath& sp)
{
	paths_t plugin_paths(get_plugin_paths (sp.get_directories ()));
	plugins_t plugins;
	
	std::transform (plugin_paths.begin(),
			plugin_paths.end(),
			std::insert_iterator<plugins_t>(plugins, plugins.begin()),
			open_plugin);

	return plugins;
}

} // namespace mojo
