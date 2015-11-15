#ifndef MOJO_ELAPSED_TIMER_H
#define MOJO_ELAPSED_TIMER_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

template <class T>
class ElapsedTimer {
public:
	ElapsedTimer()
	    : m_start_time(T::get_timestamp_microseconds())
	{
	}

	void restart() { m_start_time = T::get_timestamp_microseconds(); }

	std::uint64_t elapsed_usecs() const
	{
		return T::get_timestamp_microseconds() - m_start_time;
	}

private:
	std::uint64_t m_start_time;
};

} // namespace mojo

#endif // MOJO_ELAPSED_TIMER_H
