
#ifndef MOJO_DUMMY_ARCHIVE_INCLUDED
#define MOJO_DUMMY_ARCHIVE_INCLUDED

#include <mojo/archive.hpp>
#include <mojo/object_ptr.hpp>

#include <map>

namespace mojo {

class ObjectCollection;

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

	//typedef map<ObjectSPtr, uint64_t>

private:

	void print_object (const ObjectSPtr&);
	void print_object_collection (const ObjectCollection&);
	void print_string (const std::string&);
	void print_property (const std::string& name, const boost::any&);

};

} // namespace mojo

#endif
