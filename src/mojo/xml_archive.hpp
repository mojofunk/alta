
#ifndef MOJO_XML_ARCHIVE_INCLUDED
#define MOJO_XML_ARCHIVE_INCLUDED

#include <mojo/archive.hpp>

namespace mojo {

class XMLArchive : public Archive
{
public:

	virtual void set_property (const std::string& name,
			const boost::any& value);

	virtual void write (const std::string& file_path);
	
	virtual void read (const std::string& file_path);

	virtual void get_property (const std::string& name,
			boost::any& value);
};

} // namespace mojo

#endif
