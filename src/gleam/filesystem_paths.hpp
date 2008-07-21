#ifndef GLEAM_SYSTEM_SEARCH_PATHS
#define GLEAM_SYSTEM_SEARCH_PATHS

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
get_system_data_directories();

vector<string>
get_system_config_directories();

} // namespace gleam

#endif // GLEAM_SYSTEM_SEARCH_PATHS
