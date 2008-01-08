
#ifndef MOJO_DUMMY_ARCHIVE_INCLUDED
#define MOJO_DUMMY_ARCHIVE_INCLUDED

#include <mojo/archive.hpp>

#include <map>

namespace mojo {

using std::map;

class DummyArchive : public Archive
{
public:

	virtual void read (const std::string& file_path);

	virtual void get_property (const std::string& name, boost::any& value);

	virtual void set_property (const std::string& name, const boost::any& value);

	virtual void write (const std::string& file_path);

private:

	typedef map<std::string, boost::any> Properties;
	Properties m_properties;

};

} // namespace mojo

#endif
