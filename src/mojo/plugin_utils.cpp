#include <gmodule.h>

#include <map>

#include <mojo/plugin_utils.hpp>

#include <iostream>

using namespace std;

typedef std::pair<mojo::Plugin*, GModule*> PluginPair;

typedef std::map<std::string, PluginPair> Plugins;

namespace {

Plugins* plugin_map = 0;

mojo::Plugin*
_find_open_plugin (const std::string& path)
{
	if (plugin_map == 0)
	{
		plugin_map = new Plugins;
	}

	Plugins::const_iterator i = plugin_map->find(path);

	if (i != plugin_map->end())
	{
		return i->second.first;
	}
	return 0;
}

mojo::Plugin*
_open_plugin (const std::string& plugin_path)
{
	GModule* module = NULL;
	mojo::plugin_func_t plugin_func = 0;
	mojo::Plugin* plug;

	module = g_module_open(plugin_path.c_str(), G_MODULE_BIND_LAZY);

	if (!module)
	{
		cerr << "module == NULL:" << g_module_error() << endl;
		return 0;
	} 

	if (!g_module_symbol(module, "mojo_plugin_factory", (gpointer*)&plugin_func))
	{
		cerr << "g_module" << endl;
		return 0;
	}

	if (plugin_func == NULL)
	{
		cerr << "factory_func == NULL" << endl;
		return 0;
	}

	plug = static_cast<mojo::Plugin*>(plugin_func());

	plugin_map->insert (std::make_pair(plugin_path, std::make_pair(plug, module)));

	return plug;
}

bool
_close_plugin (mojo::Plugin* plug)
{
	for (Plugins::iterator i = plugin_map->begin();
			i != plugin_map->end(); ++i)
	{
		if (i->second.first == plug)
		{
			// have to call delete from within dll on windows?
			delete i->second.first;
			plugin_map->erase(i);
			return true;
		}
	}
	return false;
}

} // unnamed namespace

namespace mojo {

Plugin*
open_plugin (const std::string& plugin_path)
{
	Plugin* plug = _find_open_plugin(plugin_path);

	if (plug == 0)
	{
		plug = _open_plugin(plugin_path);
	}	

	return plug;
}

bool
close_plugin (Plugin* plug)
{
	return _close_plugin(plug);
}

} // namespace mojo
