#include <libgleam/filesystem_paths.hpp>

#include "debug.hpp"

namespace gleam {

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



}
