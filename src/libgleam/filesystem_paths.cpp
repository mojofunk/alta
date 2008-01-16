#include <glib.h>

#include <libgleam/filesystem_paths.hpp>

namespace gleam {

string
get_user_config_directory ()
{
	return g_get_user_config_dir();
}

string
get_user_data_directory ()
{
	return g_get_user_data_dir();
}

vector<string>
get_system_data_directories ()
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
get_system_config_directories ()
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
