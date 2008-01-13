
#ifndef MOJO_DUMMY_ARCHIVE_INCLUDED
#define MOJO_DUMMY_ARCHIVE_INCLUDED

#include <mojo/archive.hpp>
#include <mojo/object_ptr.hpp>

namespace mojo {

class ObjectCollection;

class DummyArchive : public Archive
{
public:

	virtual void write (const std::string& file_path, const Properties& props);
	
	virtual void read (const std::string& file_path, Properties& props);

private:

	void print_object (const ObjectSPtr&);
	void print_object_collection (const ObjectCollection&);
	void print_string (const std::string&);
	void print_property (const std::string& name, const boost::any&);

};

} // namespace mojo

#endif
