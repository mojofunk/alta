
#ifndef MOJO_FILESYSTEM_PATHS
#define MOJO_FILESYSTEM_PATHS

#include "search_path.hpp"
#include "filesystem.hpp"

namespace mojo {

	fs::path user_config_directory();

	Searchpath mojo_search_path();

	Searchpath system_config_search_path();

	Searchpath system_data_search_path();

	Searchpath module_search_path();

} // namespace mojo

#endif
