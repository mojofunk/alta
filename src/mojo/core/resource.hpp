#include <cstdint>

namespace mojo {

typedef uint64_t rlimit_t;

enum ResourceType {
	OpenFiles
};

struct ResourceLimit
{
	rlimit_t current_limit;
	rlimit_t max_limit;
};

/**
 * @return true on success, false on error
 */
bool
get_resource_limit (ResourceType resource, ResourceLimit& limit);

/**
 * @return true on success, false on error
 */
bool
set_resource_limit (ResourceType resource, const ResourceLimit& limit);

} // namespace mojo
