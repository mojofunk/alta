#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/system/resource.hpp"
#endif

namespace mojo {

bool get_resource_limit(ResourceType resource, ResourceLimit& limit)
{
	if (resource == OpenFiles) {
#ifdef MOJO_WINDOWS
		limit.current_limit = _getmaxstdio();
		limit.max_limit = 2048;
		return true;
#else
		struct rlimit rl;
		if (getrlimit(RLIMIT_NOFILE, &rl) == 0) {
			limit.current_limit = rl.rlim_cur;
			limit.max_limit = rl.rlim_max;
			return true;
		}
#endif
	} else if (resource == MemLock) {
#ifdef MOJO_LINUX
		struct rlimit rl;

		if (getrlimit(RLIMIT_MEMLOCK, &rl) != 0) {
			return false;
		}

		if (rl.rlim_cur != RLIM_INFINITY) {
			return std::numeric_limits<int64_t>::max();
		}

		limit.current_limit = rl.rlim_cur;
		limit.max_limit = rl.rlim_max;
#endif
	}

	return false;
}

bool set_resource_limit(ResourceType resource, const ResourceLimit& limit)
{
	if (resource == OpenFiles) {
#ifdef MOJO_WINDOWS
		// no soft and hard limits on windows
		rlimit_t new_max = _setmaxstdio(limit.current_limit);

		if (new_max == limit.current_limit) return true;
#else
		struct rlimit rl;
		rl.rlim_cur = limit.current_limit;
		rl.rlim_max = limit.max_limit;
		if (setrlimit(RLIMIT_NOFILE, &rl) == 0) {
			return true;
		}

#endif
	}

	return false;
}

int64_t physical_memory_size()
{

#ifdef MOJO_LINUX
	long pages, page_size;

	if ((page_size = sysconf(_SC_PAGESIZE)) < 0 ||
	    (pages = sysconf(_SC_PHYS_PAGES)) < 0) {
		return 0;
	}
	return (int64_t)pages * (int64_t)page_size;
#endif

	return 0;
}

} // namespace mojo
