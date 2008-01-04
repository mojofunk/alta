
#ifndef MOJO_PLUGIN_UTILS_INCLUDED
#define MOJO_PLUGIN_UTILS_INCLUDED

#include <string>

#include <mojo/plugin.hpp>

namespace mojo {

	Plugin* open_plugin (const std::string& path);

	bool close_plugin (Plugin* plug);

} // namespace mojo

#endif
