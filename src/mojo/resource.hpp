
#ifndef MOJO_RESOURCE
#define MOJO_RESOURCE

#include <inttypes.h>

namespace mojo {

	/// @return The amount of physical memory in bytes.
	int64_t physical_memory_size ();

	/**
	 * @return The maximum amount a process's address space
	 * that can be locked in memory in bytes. If lockable 
	 * memory is not limited then std::numeric_limits<int64_t>::max()
	 * will be returned.
	 */
	int64_t mlock_limit();

} // namespace mojo

#endif
