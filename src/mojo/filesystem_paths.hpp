
#ifndef MOJO_FILESYSTEM_PATHS_INCLUDED
#define MOJO_FILESYSTEM_PATHS_INCLUDED

#include <booty/filesystem.hpp>
#include <booty/search_path.hpp>

namespace mojo {

	using booty::SearchPath;

	fs::path user_config_directory();

	SearchPath mojo_search_path();

} // namespace mojo

#endif
