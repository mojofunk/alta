
#include "filesystem_paths.hpp"

#include <gleam/filesystem_paths.hpp>
#include <gleam/utils.hpp>

#ifndef MOJO_CORE_AMALGAMATED


#endif // MOJO_CORE_AMALGAMATED

namespace mojo {

fs::path
user_config_directory()
{
	return fs::path(gleam::get_user_config_directory ()) / "mojo";
}

Searchpath
mojo_search_path()
{
	return Searchpath(gleam::getenv ("MOJO_PATH"));
}

Searchpath
system_config_search_path()
{
	Searchpath sp(gleam::get_system_config_directories ());
	sp / "mojo";
	return sp;
}

Searchpath
system_data_search_path()
{
	Searchpath sp(gleam::get_system_data_directories ());
	sp / "mojo";
	return sp;
}

Searchpath
module_search_path ()
{
	return mojo_search_path ();
}

} // namespace mojo
