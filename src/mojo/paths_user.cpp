
#include <string>

using std::string;

#include <glibmm/miscutils.h>

#include <libgleam/file_utils.hpp>

#include <mojo/paths_user.hpp>
#include <mojo/directory_names.hpp>

namespace {

using namespace mojo;

const string
home_dir ()
{
	string home_dir(Glib::get_home_dir());

	if(home_dir.empty()) {

#ifdef MOJO_DEBUG
		LOG_MOJO_CRITICAL
			<< "Could not locate home directory for user"
			<< Glib::get_user_name();
#endif

	}

	return home_dir;
}

const char * const dot_prefix = ".";

const string
user_mojo_dir_name ()
{
	return string(dot_prefix) + mojo_dir_name;
}

} // anonymous namespace

namespace mojo {

namespace paths {

namespace user {

using namespace gleam;

const SearchPath
mojo_search_path ()
{
	string mojo_dir ( home_dir() / user_mojo_dir_name() );
	create_directory ( mojo_dir );
	return mojo_dir;    
}

} // namespace user

} // namespace paths

} // namespace mojo
