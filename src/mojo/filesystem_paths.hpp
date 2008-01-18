
#ifndef MOJO_FILESYSTEM_PATHS_INCLUDED
#define MOJO_FILESYSTEM_PATHS_INCLUDED

#include <mojo/filesystem.hpp>
#include <mojo/search_path.hpp>

namespace mojo {

	fs::path user_config_directory();

	SearchPath mojo_search_path();

	SearchPath system_config_search_path();

	SearchPath plugin_search_path();

} // namespace mojo

#endif
