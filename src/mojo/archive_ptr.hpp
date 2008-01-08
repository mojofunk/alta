
#ifndef MOJO_ARCHIVE_PTR_INCLUDED
#define MOJO_ARCHIVE_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class Archive;

	typedef boost::shared_ptr<Archive>    ArchiveSPtr;
	typedef boost::weak_ptr<Archive>      ArchiveWPtr;

} // namespace mojo

#endif
