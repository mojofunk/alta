#ifndef MOJO_CORE_TIME_H
#define MOJO_CORE_TIME_H

#include <cstdint>

#include "mojo/core/visibility.hpp"

namespace mojo {

/**
 * @return A monotonic time in microseconds
 */
MOJO_API uint64_t get_monotonic_time ();

}

#endif // MOJO_CORE_TIME_H
