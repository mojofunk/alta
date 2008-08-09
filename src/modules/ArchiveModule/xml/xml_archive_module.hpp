
#ifndef MOJO_XML_ARCHIVE_MODULE
#define MOJO_XML_ARCHIVE_MODULE

#include <mojo/mojo.hpp>

namespace mojo {

class XMLArchiveModule : public ArchiveModule
{
public: // constructors

	XMLArchiveModule ();
	~XMLArchiveModule ();

public: // Module interface

	virtual std::string get_author ();

	virtual std::string get_description ();

	virtual std::string get_version ();

public: // ArchiveModule Interface

	/**
	 * return new Archive or 0 on failure
	 */
	virtual ArchiveSPtr create_archive ();

};

} // namespace mojo

#endif
