
#ifndef MOJO_DUMMY_ARCHIVE_INCLUDED
#define MOJO_DUMMY_ARCHIVE_INCLUDED

#include <mojo/forward.hpp>
#include <mojo/archive.hpp>

namespace mojo {

class ObjectCollection;

class DummyArchive : public Archive
{
public:

	virtual void write (const std::string& file_path, const Properties& props);
	
	virtual void read (const std::string& file_path, Properties& props);

private:

	void write_object (std::ostream& os, const ObjectSPtr&);
	void write_object_collection (std::ostream& os, const ObjectCollection&);
	void write_property (std::ostream& os, const std::string& name, const boost::any&);

};

} // namespace mojo

#endif
