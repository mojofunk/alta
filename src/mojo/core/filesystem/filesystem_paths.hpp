#ifndef MOJO_FILESYSTEM_PATHS_H
#define MOJO_FILESYSTEM_PATHS_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"

#include "mojo/core/filesystem/search_path.hpp"
#endif

namespace mojo {

fs::path get_user_data_directory();

fs::path get_user_config_directory();

paths_t get_system_data_directories();

paths_t get_system_config_directories();

fs::path user_config_directory();

fs::path installation_directory();

Searchpath mojo_search_path();

Searchpath system_config_search_path();

Searchpath system_data_search_path();

Searchpath module_search_path();

} // namespace mojo

#endif // MOJO_FILESYSTEM_PATHS_H
