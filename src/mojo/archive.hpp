
#ifndef MOJO_ARCHIVE_INCLUDED
#define MOJO_ARCHIVE_INCLUDED

#include <string>

#include <boost/any.hpp>

namespace mojo {

/**
 * An archive needs to be able to support incremental writing so
 * that memory usage can be minimalized.
 *
 */
class Archive
{
public:

	virtual ~Archive() { }

	/**
	 * All top level objects must have a unique name
	 */
	// return error to indicate unsupported type?
	virtual void set_property (const std::string& name,
			const boost::any& value) = 0;

	virtual void write (const std::string& file_path) = 0;
	
	// read from archive
	virtual void read (const std::string& file_path) = 0;

	virtual void get_property (const std::string& name,
			boost::any& value) = 0;

};

} // namespace mojo

#endif
