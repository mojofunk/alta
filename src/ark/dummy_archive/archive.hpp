
#ifndef ARK_DUMMY_ARCHIVE_INCLUDED
#define ARK_DUMMY_ARCHIVE_INCLUDED

#include <ark/archive_reader.hpp>
#include <ark/archive_writer.hpp>

class DummyArchive : public ark::ArchiveReader, public ark::ArchiveWriter
{
public:

	DummyArchive();

	virtual ~DummyArchive();

public:

	// ArchiveReader interface
	virtual void read (const std::string& file_path);

	virtual const ark::Property get_property (const std::string& name);

public:

	// ArchiveWriter interface
	virtual void set_property (const ark::Property& prop);

	virtual void write (const std::string& file_path);

private:
	
	ark::Properties m_properties;

};

#endif
