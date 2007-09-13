
#ifndef ARK_ARCHIVE_WRITER_INCLUDED
#define ARK_ARCHIVE_WRITER_INCLUDED

#include <string>

#include <ark/object.hpp>
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
	virtual void add_object (const string& name, const Object&) = 0;

	virtual void write (const string& file_path, const TypeNameRegistry& registry) = 0;

protected:

	virtual ~ArchiveWriter() { }

};

} // namespace ark

#endif
