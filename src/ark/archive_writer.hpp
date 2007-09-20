
#ifndef ARK_ARCHIVE_WRITER_INCLUDED
#define ARK_ARCHIVE_WRITER_INCLUDED

#include <string>

#include <ark/type_name_registry.hpp>

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
	virtual void add_property (const Property& prop) = 0;

	virtual void write (const string& file_path, const TypeNameRegistry& registry) = 0;

	virtual ~ArchiveWriter() { }

};

} // namespace ark

#endif
