#include <chrono>

#ifndef MOJO_CORE_AMALGAMATED
#include "time.hpp"
#endif

namespace mojo {

uint64_t
get_monotonic_time ()
{
	using namespace std::chrono;
	auto duration = high_resolution_clock::now();
	return duration_cast<microseconds>(duration.time_since_epoch()).count();
}

} // namespace mojo
