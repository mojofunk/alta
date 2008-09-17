#include "library.hpp"

#include "glib_library.hpp" // this smells

namespace mojo {

Library::~Library () { }

LibrarySP
create_library (const fs::path& filepath)
{
	return LibrarySP(new GlibLibrary (filepath));
}

bool
is_library (const fs::path& filepath)
{
	LibrarySP tmp = create_library ("");
	return tmp->is_library (filepath); 
}

} // namespace mojo
