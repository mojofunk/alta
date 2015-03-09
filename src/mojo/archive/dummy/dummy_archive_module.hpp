
#ifndef MOJO_DUMMY_ARCHIVE_MODULE
#define MOJO_DUMMY_ARCHIVE_MODULE

#include "mojo-archive.hpp"

namespace mojo {

class DummyArchiveModule : public ArchiveModule
{
public: // constructors

	DummyArchiveModule ();
	~DummyArchiveModule ();

public: // Module interface

	virtual std::string get_author ();

	virtual std::string get_description ();

	virtual std::string get_version ();

public: // ArchiveModule Interface

	/**
	 * return new Archive or 0 on failure
	 */
	virtual ArchiveSP create_archive ();

};

} // namespace mojo

#endif
