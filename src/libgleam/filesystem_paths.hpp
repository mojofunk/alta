#ifndef GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED
#define GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED

#include <libgleam/search_path.hpp>

namespace gleam {

// XXX merge common parts into another function.

SearchPath
get_system_data_search_path()
{
	SearchPath tmp;
	const char * const * dirs;

	dirs = g_get_system_data_dirs ();

	if (dirs == NULL) return tmp;
	
	for (int i = 0; dirs[i] != NULL; i++) {
		tmp += dirs[i];
	}

#ifdef GLEAM_DEBUG_EXTRA
	LOG_GLEAM_DEBUG << tmp.get_search_path_string();
#endif

	return tmp;
}

SearchPath
get_system_config_search_path()
{
	SearchPath tmp;
	const char * const * dirs;

	dirs = g_get_system_config_dirs ();

	if (dirs == NULL) return tmp;
	
	for (int i = 0; dirs[i] != NULL; i++) {
		tmp += dirs[i];
	}

#ifdef GLEAM_DEBUG_EXTRA
	LOG_GLEAM_DEBUG << tmp.get_search_path_string();
#endif

	return tmp;
}

} // namespace gleam

#endif // GLEAM_SYSTEM_SEARCH_PATHS_INCLUDED
