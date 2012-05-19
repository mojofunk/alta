
#include "filesystem_paths.hpp"

#include <gleam/filesystem_paths.hpp>
#include <gleam/utils.hpp>

namespace mojo {

fs::path
user_config_directory()
{
	return fs::path(gleam::get_user_config_directory ()) / "mojo";
}

SearchPath
mojo_search_path()
{
	return SearchPath(gleam::getenv ("MOJO_PATH"));
}

SearchPath
system_config_search_path()
{
	SearchPath sp(gleam::get_system_config_directories ());
	sp / "mojo";
	return sp;
}

SearchPath
system_data_search_path()
{
	SearchPath sp(gleam::get_system_data_directories ());
	sp / "mojo";
	return sp;
}

SearchPath
module_search_path ()
{
	return mojo_search_path ();
}

} // namespace mojo
