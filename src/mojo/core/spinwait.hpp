#ifndef MOJO_CORE_SPINWAIT_H
#define MOJO_CORE_SPINWAIT_H

#include "mojo/core/time/timing.hpp"

namespace mojo {

inline
void
spinwait (uint64_t usecs)
{
	mojo::Timing timing;

	uint64_t i = 0;
	do {
		timing.update ();
		++i;
	} while (timing.elapsed () < usecs);
}

} // namespace mojo

#endif // MOJO_CORE_SPINWAIT_H
