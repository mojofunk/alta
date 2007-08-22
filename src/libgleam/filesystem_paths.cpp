#include <glib.h>

#include <libgleam/filesystem_paths.hpp>

namespace gleam {

vector<string>
get_system_data_search_path()
{
	vector<string> tmp;
	const char * const * dirs;

	dirs = g_get_system_data_dirs ();

	if (dirs == NULL) return tmp;
	
	for (int i = 0; dirs[i] != NULL; i++) {
		tmp.push_back( dirs[i] );
	}

	return tmp;
}

vector<string>
get_system_config_search_path()
{
	vector<string> tmp;
	const char * const * dirs;

	dirs = g_get_system_config_dirs ();

	if (dirs == NULL) return tmp;
	
	for (int i = 0; dirs[i] != NULL; i++) {
		tmp.push_back ( dirs[i] );
	}

	return tmp;
}



}
