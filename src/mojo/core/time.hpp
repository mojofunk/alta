#ifndef MOJO_CORE_TIME
#define MOJO_CORE_TIME

#include <cstdint>

#include "mojo/core/visibility.hpp"

namespace mojo {

/**
 * @return A monotonic time in microseconds
 */
MOJO_API uint64_t get_monotonic_time ();

}

#endif
