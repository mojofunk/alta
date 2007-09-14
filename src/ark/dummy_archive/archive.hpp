
#ifndef ARK_DUMMY_ARCHIVE_INCLUDED
#define ARK_DUMMY_ARCHIVE_INCLUDED

#include <ark/descriptor.hpp>

namespace ark {

class DummyDescriptor : public Descriptor
{
public:

	virtual ArchiveWriter* create_writer();
	
	virtual ArchiveReader* create_reader();

	virtual ModuleInfo get_info();

};

class DummyArchive : public ArchiveReader, public ArchiveWriter
{
public:

	DummyArchive();

	virtual ~DummyArchive();

public:

	// ArchiveReader interface
	virtual void read (const string& file_path, const TypeFactory& type_factory);

	virtual Object* get_object (const string& name);

public:

	// ArchiveWriter interface
	virtual void add_object (const string& name, const Object&);

	virtual void write (const string& file_path, const TypeNameRegistry& registry);

};

} // namespace ark
#endif
