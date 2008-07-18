
#ifndef MOJO_ARCHIVE_MODULE
#define MOJO_ARCHIVE_MODULE

#include <mojo/module.hpp>

namespace mojo {

class Archive;

class ArchiveModule : public Module
{
public: // ctors

	virtual ~ArchiveModule();

public: // Interface

	/**
	 * return new Archive or 0 on failure
	 */
	virtual Archive* create_archive () = 0;

	virtual void destroy_archive (Archive* ar) = 0; 

};

} // namespace mojo

#endif
