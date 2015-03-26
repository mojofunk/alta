#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/modules/library.hpp"
#include "mojo/core/modules/glib_library.hpp"
#endif

namespace mojo {

Library::~Library() {}

LibrarySP create_library(const fs::path& filepath)
{
	return LibrarySP(new GlibLibrary(filepath));
}

bool is_library(const fs::path& filepath)
{
	LibrarySP tmp = create_library("");
	return tmp->is_library(filepath);
}

} // namespace mojo
