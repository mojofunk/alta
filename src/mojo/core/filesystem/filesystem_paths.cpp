#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"

#include "mojo/core/system/utils.hpp"
#include "mojo/core/filesystem/filesystem_paths.hpp"
#endif

namespace mojo {

fs::path
get_user_config_directory ()
{
	return g_get_user_config_dir();
}

fs::path
get_user_data_directory ()
{
	return g_get_user_data_dir();
}

paths_t
get_system_data_directories ()
{
	paths_t tmp;
	const char * const * dirs;

	dirs = g_get_system_data_dirs ();

	if (dirs == NULL) return tmp;

	for (int i = 0; dirs[i] != NULL; i++) {
		tmp.push_back( dirs[i] );
	}

	return tmp;
}

paths_t
get_system_config_directories ()
{
	paths_t tmp;
	const char * const * dirs;

	dirs = g_get_system_config_dirs ();

	if (dirs == NULL) return tmp;

	for (int i = 0; dirs[i] != NULL; i++) {
		tmp.push_back ( dirs[i] );
	}

	return tmp;
}

fs::path
user_config_directory()
{
	return fs::path(get_user_config_directory ()) / "mojo";
}

Searchpath
mojo_search_path()
{
	return Searchpath(mojo::getenv ("MOJO_PATH"));
}

Searchpath
system_config_search_path()
{
	Searchpath sp(get_system_config_directories ());
	sp / "mojo";
	return sp;
}

Searchpath
system_data_search_path()
{
	Searchpath sp(get_system_data_directories ());
	sp / "mojo";
	return sp;
}

Searchpath
module_search_path ()
{
	return mojo_search_path ();
}

} // namespace mojo
