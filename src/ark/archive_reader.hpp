
#ifndef ARK_ARCHIVE_READER_INCLUDED
#define ARK_ARCHIVE_READER_INCLUDED

#include <string>

#include <ark/object.hpp>
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

	virtual Object* get_object (const string& name) = 0;

protected:

	virtual ~ArchiveReader() { }

};

} // namespace ark

#endif
