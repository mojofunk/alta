
#ifndef MOJO_PATHS_SYSTEM_INCLUDED
#define MOJO_PATHS_SYSTEM_INCLUDED

#include <libgleam/search_path.hpp>

namespace mojo {

using std::string;
using gleam::SearchPath;

namespace paths {

namespace system {

SearchPath data_search_path ();

SearchPath config_search_path ();

SearchPath ladspa_search_path();

SearchPath ladspa_rdf_search_path();

SearchPath module_search_path ();

SearchPath template_search_path ();

} // namespace system

} // namespace paths

} // namespace mojo

#endif // MOJO_PATHS_SYSTEM_INCLUDED
