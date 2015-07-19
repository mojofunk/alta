#ifndef MOJO_XML_ARCHIVE_MODULE_H
#define MOJO_XML_ARCHIVE_MODULE_H

#ifndef MOJO_AMALGAMATED
#include "mojo/archive/archive_module.hpp"
#endif

namespace mojo {

class XMLArchiveModule : public ArchiveModule {
public: // constructors
	XMLArchiveModule();
	~XMLArchiveModule();

public: // Module interface
	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // ArchiveModule Interface
	       /**
	        * return new Archive or 0 on failure
	        */
	virtual ArchiveSP create_archive();
};

} // namespace mojo

#endif // MOJO_XML_ARCHIVE_MODULE_H
