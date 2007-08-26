
#include <mojo/filesystem_paths.hpp>

#include <libgleam/utils.hpp>

namespace mojo {

fs::path
user_config_directory()
{

	return fs::path();
}

SearchPath
mojo_search_path()
{
	return SearchPath( gleam::getenv ("MOJO_PATH") );
}

}
