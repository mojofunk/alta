#ifndef GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED
#define GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED

#include <libgleam/search_path.hpp>

namespace gleam {

SearchPath
get_system_data_search_path();

SearchPath
get_system_config_search_path();

} // namespace gleam

#endif // GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED
