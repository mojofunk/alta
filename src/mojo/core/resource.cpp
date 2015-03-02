#ifdef _WIN32
#include <stdio.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif

#include "resource.hpp"

namespace mojo {

bool
get_resource_limit (ResourceType resource, ResourceLimit& limit)
{
	if (resource == OpenFiles)
	{
#ifdef _WIN32
		limit.current_limit = _getmaxstdio();
		limit.max_limit = 2048;
		return true;
#else
		struct rlimit rl;
		if (getrlimit (RLIMIT_NOFILE, &rl) == 0) {
			limit.current_limit = rl.rlim_cur;
			limit.max_limit = rl.rlim_max;
			return true;
		}
#endif
	}

	return false;
}

bool
set_resource_limit (ResourceType resource, const ResourceLimit& limit)
{
	if (resource == OpenFiles)
	{
#ifdef _WIN32
		// no soft and hard limits on windows
		rlimit_t new_max = _setmaxstdio(limit.current_limit);

		if (new_max == limit.current_limit) return true;
#else
		struct rlimit rl;
		rl.rlim_cur = limit.current_limit;
		rl.rlim_max = limit.max_limit;
		if (setrlimit (RLIMIT_NOFILE, &rl) == 0) {
			return true;
		}

#endif
	}

	return false;
}

} // namespace mojo
