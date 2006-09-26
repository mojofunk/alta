
#include <string>

using std::string;

#include <glibmm/miscutils.h>

#include <libgleam/file_utils.hpp>

#include <libmojo/paths_user.hpp>
#include <libmojo/dir_names.hpp>

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

const string
user_ladspa_dir_name ()
{
	return string(dot_prefix) + ladspa_dir_name;
}

const string
user_vst_dir_name ()
{
	return string(dot_prefix) + vst_dir_name;
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

const SearchPath
ladspa_search_path ()
{
	string ladspa_dir ( home_dir() / user_ladspa_dir_name() );
	create_directory ( ladspa_dir );
	return ladspa_dir;
}

const SearchPath
ladspa_rdf_search_path ()
{
	string ladspa_rdf_dir ( home_dir() / user_ladspa_dir_name() / rdf_dir_name );
	create_directory ( ladspa_rdf_dir );
	return ladspa_rdf_dir;
}

const SearchPath
vst_search_path ()
{
	string vst_dir ( home_dir() / user_vst_dir_name() );
	create_directory ( vst_dir );
	return vst_dir;
}

const SearchPath
vst_rdf_search_path ()
{
	string vst_rdf_dir ( home_dir() / user_vst_dir_name() / rdf_dir_name );
	create_directory ( vst_rdf_dir );
	return vst_rdf_dir;
}

} // namespace user

} // namespace paths

} // namespace mojo
