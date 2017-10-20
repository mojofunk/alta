#ifndef MOJO_CORE_SPINWAIT_H
#define MOJO_CORE_SPINWAIT_H

inline void
spinwait(uint64_t usecs)
{
	mojo::Timing timing;

	uint64_t i = 0;
	do {
		timing.update();
		++i;
	} while (timing.elapsed() < usecs);
}

#endif // MOJO_CORE_SPINWAIT_H
