
#ifndef ARK_ARCHIVE_WRITER_INCLUDED
#define ARK_ARCHIVE_WRITER_INCLUDED

#include <string>

#include <ark/property.hpp>

namespace ark {

/**
 *
 */
class ArchiveWriter
{
public:

	/**
	 * All top level objects must have a unique name
	 */
	virtual void set_property (const Property& prop) = 0;

	virtual void write (const string& file_path) = 0;

	virtual ~ArchiveWriter() { }

};

} // namespace ark

#endif
