#include "time.hpp"

#include <chrono>

namespace mojo {

uint64_t
get_monotonic_time ()
{
	using namespace std::chrono;
	auto duration = high_resolution_clock::now();
	return duration_cast<microseconds>(duration.time_since_epoch()).count();
}

}
