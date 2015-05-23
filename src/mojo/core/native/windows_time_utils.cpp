#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/debug/debug.hpp"
#include "mojo/core/string/compose.hpp"
#include "mojo/core/native/windows_source_includes.hpp"
#include "mojo/core/native/windows_time_utils.hpp"
#endif

MOJO_DEBUG_DOMAIN(WINDOWS_TIME_UTILS)

namespace {

LARGE_INTEGER
get_frequency()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return freq;
}

UINT& old_timer_resolution()
{
	static UINT timer_res_ms = 0;
	return timer_res_ms;
}

} // anon namespace

namespace mojo {

namespace utils {

bool get_mm_timer_resolution(uint32_t& timer_resolution_ms)
{
	TIMECAPS caps;

	if (timeGetDevCaps(&caps, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
		MOJO_DEBUG_MSG(WINDOWS_TIME_UTILS, "Could not get timer device capabilities");
		return false;
	}
	timer_resolution_ms = caps.wPeriodMin;
	return true;
}

bool set_mm_timer_resolution(uint32_t timer_resolution_ms)
{
	TIMECAPS caps;

	if (timeGetDevCaps(&caps, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
		MOJO_DEBUG_MSG(WINDOWS_TIME_UTILS, "Could not get timer device capabilities");
		return false;
	}

	UINT old_min_resolution = caps.wPeriodMin;

	if (timeBeginPeriod(timer_resolution_ms) != TIMERR_NOERROR) {
		MOJO_DEBUG_MSG(WINDOWS_TIME_UTILS,
		               compose("Could not set minimum timer resolution to %(ms)",
		                       timer_resolution_ms));
		return false;
	}

	old_timer_resolution() = old_min_resolution;

	MOJO_DEBUG_MSG(
	    WINDOWS_TIME_UTILS,
	    compose("Multimedia timer resolution set to %(ms)", timer_resolution_ms));

	return true;
}

bool reset_mm_timer_resolution()
{
	if (old_timer_resolution()) {
		if (timeEndPeriod(old_timer_resolution()) != TIMERR_NOERROR) {
			MOJO_DEBUG_MSG(WINDOWS_TIME_UTILS, "Could not reset timer resolution");
			return false;
		}
	}

	MOJO_DEBUG_MSG(WINDOWS_TIME_UTILS,
	               compose("Multimedia timer resolution reset to %(ms)",
	                       old_timer_resolution()));

	return true;
}

uint64_t performance_counter_us()
{
	static LARGE_INTEGER frequency = get_frequency();
	LARGE_INTEGER current_val;

	QueryPerformanceCounter(&current_val);

	return (uint64_t)(((double)current_val.QuadPart) /
	                  ((double)frequency.QuadPart) * 1000000.0);
}

} // namespace utils

} // namespace mojo
