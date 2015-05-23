#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_windows_time_utils
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/string/compose.hpp"

#include "mojo/core/native/windows_time_utils.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

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
