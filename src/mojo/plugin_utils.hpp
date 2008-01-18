
#ifndef MOJO_PLUGIN_UTILS_INCLUDED
#define MOJO_PLUGIN_UTILS_INCLUDED

#include <set>

#include <mojo/plugin_ptr.hpp>
#include <mojo/filesystem.hpp>
#include <mojo/search_path.hpp>
#include <mojo/plugin_set.hpp>

namespace mojo {

	typedef std::vector<fs::path> paths_t;

	// need a way to automatically close plugin
	PluginSPtr open_plugin (const fs::path& filepath);

	bool is_plugin_file (const fs::path& filepath);

	paths_t get_plugin_paths (const paths_t& directories);

	PluginSet discover_plugins (const SearchPath& sp);
	
} // namespace mojo

#endif
