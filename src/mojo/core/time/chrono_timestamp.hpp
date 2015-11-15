#ifndef MOJO_CHRONO_TIMESTAMP_H
#define MOJO_CHRONO_TIMESTAMP_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

class ChronoTimeStamp {
public:
	static uint64_t get_microseconds()
	{
		auto duration = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(
		           duration.time_since_epoch()).count();
	}
};

} // namespace mojo

#endif // MOJO_CHRONO_TIMESTAMP_H
