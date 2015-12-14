#ifndef MOJO_LOGGING_TIMESTAMP_H
#define MOJO_LOGGING_TIMESTAMP_H

namespace logging {

class TimeStamp {
public:
	static uint64_t get_microseconds()
	{
		auto duration = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(
		           duration.time_since_epoch()).count();
	}
};

} // namespace logging

#endif // MOJO_LOGGING_TIMESTAMP_H
