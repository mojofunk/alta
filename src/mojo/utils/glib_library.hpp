
#ifndef MOJO_GLIB_LIBRARY
#define MOJO_GLIB_LIBRARY

#include <gmodule.h>

#include "library.hpp"

namespace mojo {

class GlibLibrary : public Library
{
public: // constructors

	GlibLibrary (const fs::path& filepath);

public: // Library Interface

	fs::path get_filepath () const;

	bool open ();
	bool close ();

	std::string get_error_string () const;

	void * resolve (const std::string& symbol_name);

	bool is_library (const fs::path& filepath);

private:

	fs::path m_filepath;

	GModule* m_module;

};


} // namespace mojo

#endif
