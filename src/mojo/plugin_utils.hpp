
#ifndef MOJO_PLUGIN_UTILS_INCLUDED
#define MOJO_PLUGIN_UTILS_INCLUDED

#include <mojo/plugin_ptr.hpp>

#include <mojo/filesystem.hpp>

namespace mojo {

	// need a way to automatically close plugin
	PluginSPtr open_plugin (const fs::path& filepath);

	bool is_plugin_file (const fs::path& filepath);

} // namespace mojo

#endif
