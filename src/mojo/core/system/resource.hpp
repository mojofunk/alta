#ifndef MOJO_RESOURCE_H
#define MOJO_RESOURCE_H

// TODO make into class

typedef uint64_t rlimit_t;

enum ResourceType { OpenFiles, MemLock };

struct ResourceLimit {
	rlimit_t current_limit;
	rlimit_t max_limit;
};

/**
 * @return true on success, false on error
 */
bool
get_resource_limit(ResourceType resource, ResourceLimit& limit);

/**
 * @return true on success, false on error
 */
bool
set_resource_limit(ResourceType resource, const ResourceLimit& limit);

/// @return The amount of physical memory in bytes
int64_t
physical_memory_size();

#endif // MOJO_RESOURCE_H
