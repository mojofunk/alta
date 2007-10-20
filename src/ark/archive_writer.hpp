
#ifndef ARK_ARCHIVE_WRITER_INCLUDED
#define ARK_ARCHIVE_WRITER_INCLUDED

#include <string>

#include <boost/any.hpp>

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
	virtual void set_property (const std::string& name, const boost::any& value) = 0;

	virtual void write (const std::string& file_path) = 0;

	virtual ~ArchiveWriter() { }

};

} // namespace ark

#endif
