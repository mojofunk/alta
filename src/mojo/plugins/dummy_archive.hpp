
#ifndef MOJO_DUMMY_ARCHIVE_INCLUDED
#define MOJO_DUMMY_ARCHIVE_INCLUDED

#include <mojo/archive_reader.hpp>
#include <mojo/archive_writer.hpp>

#include <map>

using std::map;

class DummyArchive : public mojo::ArchiveReader, public mojo::ArchiveWriter
{
public:

	// ArchiveReader interface
	virtual void read (const std::string& file_path);

	virtual void get_property (const std::string& name, boost::any& value);

public:

	// ArchiveWriter interface
	virtual void set_property (const std::string& name, const boost::any& value);

	virtual void write (const std::string& file_path);

private:

	typedef map<std::string, boost::any> Properties;
	Properties m_properties;

};

#endif