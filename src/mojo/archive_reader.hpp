
#ifndef MOJO_ARCHIVE_READER_INCLUDED
#define MOJO_ARCHIVE_READER_INCLUDED

#include <string>

#include <boost/any.hpp>

namespace mojo {

/**
 *
 */
class ArchiveReader
{
public:

	// read from archive
	virtual void read (const std::string& file_path) = 0;

	virtual void get_property (const std::string& name, boost::any& value) = 0;

	virtual ~ArchiveReader() { }

};

} // namespace mojo

#endif