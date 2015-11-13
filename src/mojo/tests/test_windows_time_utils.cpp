#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_windows_time_utils
#endif

#include "test_includes.hpp"

BOOST_AUTO_TEST_CASE(test_windows_time_utils_basic)
{
	uint32_t orig_res = 0;
	BOOST_CHECK(utils::get_mm_timer_resolution(orig_res));

	BOOST_TEST_MESSAGE(compose("Original min MM timer resolution: %", orig_res));

	BOOST_CHECK(utils::set_mm_timer_resolution(1));

	BOOST_CHECK(utils::reset_mm_timer_resolution());
	uint32_t current_res = 0;

	// check that reset was successful
	BOOST_CHECK(utils::get_mm_timer_resolution(current_res));
	BOOST_CHECK(current_res == orig_res);
}
