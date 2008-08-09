#include "library.hpp"

#include "glib_library.hpp" // this smells

namespace mojo {

Library::~Library () { }

LibrarySPtr
create_library (const fs::path& filepath)
{
	return LibrarySPtr(new GlibLibrary (filepath));
}

bool
is_library (const fs::path& filepath)
{
	LibrarySPtr tmp = create_library ("");
	return tmp->is_library (filepath); 
}

} // namespace mojo
