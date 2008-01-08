
#include <mojo/archive_utils.hpp>

#include <mojo/dummy_archive.hpp>

namespace mojo {

ArchiveSPtr
create_mojo_archive()
{
	return ArchiveSPtr(new DummyArchive);
}

} // namespace mojo
