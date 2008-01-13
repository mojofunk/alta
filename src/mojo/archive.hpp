
#ifndef MOJO_ARCHIVE_INCLUDED
#define MOJO_ARCHIVE_INCLUDED

#include <string>

#include <mojo/properties.hpp>

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
public:

	virtual ~Archive() { }

	virtual void write (const std::string& file_path, const Properties& props) = 0;
	
	virtual void read (const std::string& file_path, Properties& props) = 0;

};

} // namespace mojo

#endif
