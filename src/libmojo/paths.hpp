
#ifndef MOJO_PATHS_INCLUDED
#define MOJO_PATHS_INCLUDED

#include <libgleam/path_string.hpp>

namespace mojo {

using gleam::path_string;

namespace paths {

	const path_string mojo_env_path_string ();

	const path_string config_path_string ();
	
	const path_string pixmap_path_string ();

	const path_string ladspa_path_string ();

	const path_string ladspa_rdf_path_string ();

	const path_string vst_path_string ();

	const path_string vst_rdf_path_string ();

} // namespace paths

} // namespace mojo

#endif // MOJO_PATHS_INCLUDED
