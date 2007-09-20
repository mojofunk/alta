
#ifndef ARK_ARCHIVE_READER_INCLUDED
#define ARK_ARCHIVE_READER_INCLUDED

#include <string>

#include <ark/type_factory.hpp>

namespace ark {

/**
 *
 */
class ArchiveReader
{
public:

	// read from archive

	virtual void read (const string& file_path, const TypeFactory& type_factory) = 0;

	virtual const Property get_property (const string& name) = 0;

	virtual ~ArchiveReader() { }

};

} // namespace ark

#endif
