#ifndef MOJO_DUMMY_ARCHIVE_H
#define MOJO_DUMMY_ARCHIVE_H

class DummyArchive : public Archive
{
public: // Archive interface
	virtual void write(const fs::path& file_path, const Properties& props);

	virtual void read(const fs::path& file_path, Properties& props);

private:
	void write_object(std::ostream& os, const ObjectSP&);
	void write_object_collection(std::ostream& os, const ObjectCollection&);
	void write_property(std::ostream& os, const Property& prop);
};

#endif // MOJO_DUMMY_ARCHIVE_H
