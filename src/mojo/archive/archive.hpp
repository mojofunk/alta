#ifndef MOJO_CORE_ARCHIVE_H
#define MOJO_CORE_ARCHIVE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/filesystem/filesystem.hpp"
#include "mojo/core/object/properties.hpp"
#endif

namespace mojo {

/**
 * An archive needs to be able to support incremental writing so
 * that memory usage can be minimalized.
 *
 * An archive does not have to know about all class types. It just
 * has to know about any fundamental types it supports and the 
 * mojo::Object class
 *
 * An archive implementation uses the type system to get a name
 * that maps to a particular type for storing in the archive. This
 * type name can then be used to create instances of that class
 * when the archive is read from disk.
 *
 * Archive needs to be more explicit in what types are supported
 */
class Archive
{
public: // ctors

	virtual ~Archive();

public: // Interface

	virtual void write (const fs::path& file_path, const Properties& props) = 0;
	
	virtual void read (const fs::path& file_path, Properties& props) = 0;

};

} // namespace mojo

#endif // MOJO_CORE_ARCHIVE_H
