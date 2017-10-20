#ifndef MOJO_CHRONO_TIMESTAMP_H
#define MOJO_CHRONO_TIMESTAMP_H

class ChronoTimeStamp
{
public:
	static uint64_t get_microseconds()
	{
		auto duration = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(
		           duration.time_since_epoch())
		    .count();
	}
};

#endif // MOJO_CHRONO_TIMESTAMP_H
