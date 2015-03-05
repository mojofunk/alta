#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source.hpp"
#include "mojo/core/modules/glib_library.hpp"
#endif

namespace mojo {

GlibLibrary::GlibLibrary (const fs::path& library_path)
	: m_filepath(library_path)
	, m_module(NULL)
{ }

fs::path
GlibLibrary::get_filepath () const
{
	return m_filepath;
}

bool
GlibLibrary::open ()
{
	m_module = g_module_open(m_filepath.string().c_str(),
		       	G_MODULE_BIND_LAZY);

	if (m_module == NULL)
	{
		return false;
	} 

	return true;
}

bool
GlibLibrary::close ()
{
	return g_module_close (m_module);
}

std::string
GlibLibrary::get_error_string () const
{
	return g_module_error ();
}

void *
GlibLibrary::resolve (const std::string& symbol_name)
{
	if (!open ()) return NULL;

	gpointer func;

	if (g_module_symbol(m_module, symbol_name.c_str(), &func) == FALSE)
	{
		return NULL;
	}

	if (func == NULL)
	{
		return NULL;
	}

	return func;
}

bool
GlibLibrary::is_library (const fs::path& filepath)
{
	return (fs::extension (filepath) == "." G_MODULE_SUFFIX);
}

} // namespace mojo
