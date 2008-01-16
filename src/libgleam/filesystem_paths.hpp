#ifndef GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED
#define GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED

#include <vector>
#include <string>

namespace gleam {

using std::vector;
using std::string;

string
get_user_config_directory ();

string
get_user_data_directory ();

vector<string>
get_system_data_search_path();

vector<string>
get_system_config_search_path();

} // namespace gleam

#endif // GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED
