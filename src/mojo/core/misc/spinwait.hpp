#ifndef MOJO_CORE_SPINWAIT_H
#define MOJO_CORE_SPINWAIT_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/time/timing.hpp"
#endif

namespace mojo {

inline void spinwait(uint64_t usecs)
{
	mojo::Timing timing;

	uint64_t i = 0;
	do {
		timing.update();
		++i;
	} while (timing.elapsed() < usecs);
}

} // namespace mojo

#endif // MOJO_CORE_SPINWAIT_H
