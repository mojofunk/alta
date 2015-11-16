#ifndef MOJO_WINDOWS_TIME_UTILS_H
#define MOJO_WINDOWS_TIME_UTILS_H

#include <cstdint>

namespace utils {

bool get_mm_timer_resolution(uint32_t& timer_resolution_us);

bool set_mm_timer_resolution(uint32_t timer_resolution_us);

bool reset_mm_timer_resolution();

uint64_t time_get_time_ms();

uint64_t performance_counter_us();

} // namespace utils

#endif // MOJO_WINDOWS_TIME_UTILS_H
