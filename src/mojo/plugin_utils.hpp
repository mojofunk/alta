
#ifndef MOJO_PLUGIN_UTILS_INCLUDED
#define MOJO_PLUGIN_UTILS_INCLUDED

#include <mojo/plugin.hpp>

#include <mojo/filesystem.hpp>

namespace mojo {

	// need a way to automatically close plugin
	Plugin* open_plugin (const fs::path& filepath);

	bool close_plugin (Plugin* plug);

	bool is_plugin_file (const fs::path& filepath);

} // namespace mojo

#endif
