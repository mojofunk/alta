#ifndef MOJO_ARCHIVE_MODULE_H
#define MOJO_ARCHIVE_MODULE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#include "mojo/core/interfaces/typedefs.hpp"
#include "mojo/core/modules/module.hpp"
#endif

namespace mojo {

class ArchiveModule : public Module
{
public: // ctors

	virtual ~ArchiveModule();

public: // Interface

	/**
	 * return new Archive or 0 on failure
	 */
	virtual ArchiveSP create_archive () = 0;

};

} // namespace mojo

#endif // MOJO_ARCHIVE_MODULE_H
