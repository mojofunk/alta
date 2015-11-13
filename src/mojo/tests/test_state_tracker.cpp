#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_state_tracker
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

BOOST_AUTO_TEST_CASE(test_state_tracker)
{
	StateTrackerSP st(new StateTracker());

	BOOST_REQUIRE(st);
}
