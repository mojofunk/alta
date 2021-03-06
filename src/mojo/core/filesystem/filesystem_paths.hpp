#ifndef MOJO_FILESYSTEM_PATHS_H
#define MOJO_FILESYSTEM_PATHS_H

fs::path
get_user_data_directory();

fs::path
get_user_config_directory();

paths_t
get_system_data_directories();

paths_t
get_system_config_directories();

fs::path
user_config_directory();

fs::path
installation_directory();

Searchpath
mojo_search_path();

Searchpath
system_config_search_path();

Searchpath
system_data_search_path();

Searchpath
module_search_path();

#endif // MOJO_FILESYSTEM_PATHS_H
