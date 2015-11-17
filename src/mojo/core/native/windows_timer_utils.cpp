MOJO_DEBUG_DOMAIN(WINDOWS_TIMER_UTILS)

namespace {

static
UINT&
mmtimer_resolution ()
{
	static UINT timer_res_ms = 0;
	return timer_res_ms;
}

} // namespace

namespace mmtimers {

bool
get_min_resolution (uint32_t& min_resolution_ms)
{
	TIMECAPS caps;

	if (timeGetDevCaps (&caps, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
		MOJO_DEBUG_MSG(WINDOWS_TIMER_UTILS, "Could not get timer device capabilities")
		return false;
	}

	min_resolution_ms = caps.wPeriodMin;
	return true;
}

bool
set_min_resolution ()
{
	uint32_t min_resolution = 0;

	if (!get_min_resolution (min_resolution)) {
		return false;
	}

	if (!set_resolution (min_resolution)) {
		return false;
	}
	return true;
}

bool
set_resolution (uint32_t timer_resolution_ms)
{
	if (mmtimer_resolution() != 0) {
		MOJO_DEBUG_MSG(
		    WINDOWS_TIMER_UTILS,
		    "Timer resolution must be reset before setting new resolution.");
	}

	if (timeBeginPeriod(timer_resolution_ms) != TIMERR_NOERROR) {
		MOJO_DEBUG_MSG(
		    WINDOWS_TIMER_UTILS,
		    compose("Could not set timer resolution to %(ms)", timer_resolution_ms));
		return false;
	}

	mmtimer_resolution() = timer_resolution_ms;

	MOJO_DEBUG_MSG(WINDOWS_TIMER_UTILS,
	               compose("Multimedia timer resolution set to %(ms)",
	                       timer_resolution_ms));
	return true;
}

bool
reset_resolution ()
{
	// You must match calls to timeBegin/EndPeriod with the same resolution
	if (timeEndPeriod(mmtimer_resolution()) != TIMERR_NOERROR) {
		MOJO_DEBUG_MSG(WINDOWS_TIMER_UTILS,
		               "Could not reset the Timer resolution.");
		return false;
	}
	MOJO_DEBUG_MSG(WINDOWS_TIMER_UTILS, "Reset the Timer resolution.");
	mmtimer_resolution() = 0;
	return true;
}

} // namespace mmtimers

namespace {

static double timer_rate_us = 0.0;

static
bool
test_qpc_validity ()
{
	int64_t last_timer_val = qpc::get_microseconds ();
	if (last_timer_val < 0) return false;

	for (int i = 0; i < 100000; ++i) {
		int64_t timer_val = qpc::get_microseconds ();
		if (timer_val < 0) return false;
		// try and test for non-syncronized TSC(AMD K8/etc)
		if (timer_val < last_timer_val) return false;
		last_timer_val = timer_val;
	}
	return true;
}

} // namespace

namespace qpc {

bool
check_timer_valid ()
{
	if (!timer_rate_us) {
		return false;
	}
	return test_qpc_validity ();
}

bool
initialize ()
{
	LARGE_INTEGER freq;
	if (!QueryPerformanceFrequency(&freq) || freq.QuadPart < 1) {
		MOJO_DEBUG_MSG(WINDOWS_TIMER_UTILS, "Failed to determine frequency of QPC");
		timer_rate_us = 0;
	} else {
		timer_rate_us = 1000000.0 / freq.QuadPart;
	}
	MOJO_DEBUG_MSG(WINDOWS_TIMER_UTILS,
	               compose("QPC timer microseconds per tick: %", timer_rate_us));
	return !timer_rate_us;
}

int64_t
get_microseconds ()
{
	LARGE_INTEGER current_val;

	if (timer_rate_us) {
		// MS docs say this will always succeed for systems >= XP but it may
		// not return a monotonic value with non-invariant TSC's etc
		if (QueryPerformanceCounter(&current_val) != 0) {
			return (int64_t)(current_val.QuadPart * timer_rate_us);
		}
	}
	MOJO_DEBUG_MSG(WINDOWS_TIMER_UTILS, "Could not get QPC timer.");
	return -1;
}

} // namespace qpc
