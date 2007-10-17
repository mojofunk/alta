
#ifndef ARK_ARCHIVE_READER_INCLUDED
#define ARK_ARCHIVE_READER_INCLUDED

#include <string>

#include <ark/property.hpp>

namespace ark {

/**
 *
 */
class ArchiveReader
{
public:

	// read from archive
	virtual void read (const std::string& file_path) = 0;

	virtual const Property get_property (const std::string& name) = 0;

	virtual ~ArchiveReader() { }

};

} // namespace ark

#endif
