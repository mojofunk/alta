#ifndef MOJO_FILESYSTEM_PATHS_H
#define MOJO_FILESYSTEM_PATHS_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"

#include "mojo/core/filesystem/search_path.hpp"
#endif

namespace mojo {

	fs::path user_config_directory();

	Searchpath mojo_search_path();

	Searchpath system_config_search_path();

	Searchpath system_data_search_path();

	Searchpath module_search_path();

} // namespace mojo

#endif // MOJO_FILESYSTEM_PATHS_H
