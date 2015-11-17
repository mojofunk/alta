#ifndef MOJO_WINDOWS_TIMER_UTILS_H
#define MOJO_WINDOWS_TIMER_UTILS_H

namespace mmtimers {

/**
 * Get the minimum Multimedia Timer resolution as supported by the system
 * @return true if getting min timer resolution was not successful
 */
bool MOJO_API get_min_resolution (uint32_t& timer_resolution_ms);

/**
 * Set the minimum Multimedia Timer resolution as supported by the system
 * @return true if setting min timer resolution was successful
 */
bool MOJO_API set_min_resolution ();

/**
 * Set current Multimedia Timer resolution. If the timer resolution has already
 * been set then reset_resolution() must be called before set_resolution will
 * succeed.
 * @return true if setting the timer value was successful, false if setting the
 * timer resolution failed or the resolution has already been set.
 */
bool MOJO_API set_resolution(uint32_t timer_resolution_ms);

/**
 * Reset Multimedia Timer resolution. In my testing, if the timer resolution is
 * set below the default, then resetting the resolution will not reset the
 * timer resolution back to 15ms. At least it does not reset immediately
 * even after calling Sleep.
 * @return true if setting the timer value was successful
 */
bool MOJO_API reset_resolution();

} // namespace mmtimers

namespace qpc {

/**
 * Initialize the QPC timer, must be called before QPC::get_microseconds will
 * return a valid value.
 * @return true if QPC timer is usable, use check_timer_valid to try to check
 * if it is monotonic.
 */
bool MOJO_API initialize ();

/**
 * @return true if QueryPerformanceCounter is usable as a timer source
 * This should always return true for systems > XP as those versions of windows
 * have there own tests to check timer validity and will select an appropriate
 * timer source. This check is not conclusive and there are probably conditions
 * under which this check will return true but the timer is not monotonic.
 */
bool MOJO_API check_timer_valid ();

/**
 * @return the value of the performance counter converted to microseconds
 *
 * If initialize returns true then get_microseconds will always return a
 * positive value. If QPC is not supported(OS < XP) then -1 is returned but the
 * MS docs say that this won't occur for systems >= XP.
 */
int64_t MOJO_API get_microseconds ();

} // namespace qpc

#endif // MOJO_WINDOWS_TIMER_UTILS_H
