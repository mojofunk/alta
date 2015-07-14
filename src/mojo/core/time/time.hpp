#ifndef MOJO_CORE_TIME_H
#define MOJO_CORE_TIME_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

/**
 * @return A monotonic time in microseconds
 */
MOJO_API uint64_t get_monotonic_time();

MOJO_API void usleep(uint64_t microseconds);

MOJO_API void sleep(uint32_t seconds);

}

#endif // MOJO_CORE_TIME_H
