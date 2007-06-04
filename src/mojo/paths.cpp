
#include <glibmm/miscutils.h>

#include <mojo/paths.hpp>
#include <mojo/paths_user.hpp>
#include <mojo/paths_system.hpp>

namespace mojo {

namespace paths {

SearchPath
mojo_env_search_path ()
{
	return Glib::getenv("MOJO_PATH");
}

SearchPath
config_search_path ()
{
	return SearchPath
		(
		 mojo_env_search_path() + 
		 paths::user::mojo_search_path() + 
		 paths::system::config_search_path()
		);
}

} // namespace paths

} // namespace mojo

