
#ifndef MOJO_ARCHIVE_WRITER_INCLUDED
#define MOJO_ARCHIVE_WRITER_INCLUDED

#include <string>

#include <boost/any.hpp>

namespace mojo {

/**
 *
 */
class ArchiveWriter
{
public:

	/**
	 * All top level objects must have a unique name
	 */
	// return error to indicate unsupported type?
	virtual void set_property (const std::string& name, const boost::any& value) = 0;

	virtual void write (const std::string& file_path) = 0;

	virtual ~ArchiveWriter() { }

};

} // namespace mojo

#endif