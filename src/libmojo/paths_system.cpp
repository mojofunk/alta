
#include <glib.h>

#include <glibmm/miscutils.h>

#include <libgleam/filesystem_paths.hpp>

#include <libmojo/paths_system.hpp>
#include <libmojo/directory_names.hpp>

#include <libmojo/debug.hpp>

namespace mojo {

namespace paths {

namespace system {

SearchPath
data_search_path ()
{
#ifdef WITH_STATIC_PATHS
	return Glib::build_filename (DATA_DIR, mojo_dir_name);
#else
	return gleam::get_system_data_search_path() / mojo_dir_name;
#endif
}

SearchPath
config_search_path ()
{
#ifdef WITH_STATIC_PATHS
	return Glib::build_filename (CONFIG_DIR, mojo_dir_name);
#else
	return gleam::get_system_config_search_path() / mojo_dir_name;
#endif
}

// XXX todo
SearchPath
ladspa_search_path ()
{
	return SearchPath("");
}

// XXX todo
SearchPath
ladspa_rdf_search_path ()
{

	return SearchPath("");
}

SearchPath
module_search_path ()
{
#ifdef WITH_STATIC_PATHS
	return SearchPath(MODULE_DIR);
#else
	// XXX todo
	return SearchPath("");
#endif
}

SearchPath
template_search_path ()
{
#ifdef WITH_STATIC_PATHS
	return SearchPath(TEMPLATE_DIR);
#else
	return data_search_path() / template_dir_name;
#endif
}

} // namespace system

} // namespace paths

} // namespace mojo
