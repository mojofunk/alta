
#ifndef ARK_MODULE_INCLUDED
#define ARK_MODULE_INCLUDED

// to remove don't pollute with C headers
#include <gmodule.h>

#include <ark/module_api.hpp>

#include <ark/descriptor.hpp>

namespace ark {

/**
 * The Module class represents a loaded module. When the Module
 * goes out of scope the module is unloaded/closed
 */
class Module
{
public:

	/**
	 * Load the module and resolve symbols, or throw
	 */
	Module(const string& module_file_path);

	/**
	 * unload module
	 */
	~Module();

	ModuleInfo get_info() const;

	/**
	 * Caller is responsible for deleting returned project
	 */
	ArchiveReader* new_reader (const ArchiveFormat& format);

	ArchiveWriter* new_writer (const ArchiveFormat& format);

private:

	// constructors
	Module(const Module&);
	Module();

	bool resolve_symbol (const string& name, void*& symbol);

private:

	// members
	GModule* m_module;

	Descriptor* m_desc;

};

} // namespace ark

#endif
