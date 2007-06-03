
#ifndef MOJO_PATHS_INCLUDED
#define MOJO_PATHS_INCLUDED

#include <libgleam/search_path.hpp>

namespace mojo {

using gleam::SearchPath;

namespace paths {

	SearchPath mojo_env_search_path ();

	SearchPath config_search_path ();

} // namespace paths

} // namespace mojo

#endif // MOJO_PATHS_INCLUDED
