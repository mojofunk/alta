
#ifndef MOJO_PATHS_USER_INCLUDED
#define MOJO_PATHS_USER_INCLUDED

#include <libgleam/search_path.hpp>

namespace mojo {

using gleam::SearchPath;

namespace paths {

namespace user {
	
	const SearchPath mojo_search_path ();

	const SearchPath vst_search_path ();
	
	const SearchPath vst_rdf_search_path ();

	const SearchPath ladspa_search_path ();

	const SearchPath ladspa_rdf_search_path ();
	
} // namespace user

} // namespace paths

} // namespace mojo

#endif // MOJO_PATHS_USER_INCLUDED
