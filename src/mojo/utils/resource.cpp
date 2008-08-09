
#ifdef __linux__
#include <unistd.h>
#include <sys/resource.h>
#endif

#include <limits>

#include "resource.hpp"

namespace mojo {

int64_t
physical_memory_size ()
{

#ifdef __linux__
	long pages, page_size;

	if ((page_size = sysconf (_SC_PAGESIZE)) < 0 || (pages = sysconf (_SC_PHYS_PAGES)) < 0) {
		return 0;
	}
	return (int64_t) pages * (int64_t) page_size;
#endif

	return 0;
}

int64_t
mlock_limit()
{

#ifdef __linux__
	struct rlimit limits;

	if (getrlimit (RLIMIT_MEMLOCK, &limits) != 0) return 0;

	if (limits.rlim_cur != RLIM_INFINITY) {
		return std::numeric_limits<int64_t>::max();
	}

	return limits.rlim_cur;
#endif

	return 0;
}

} // namespace mojo
