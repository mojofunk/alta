
#define BOOST_TEST_MODULE mojo_state_tracker

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <mojo/core/typedefs.hpp>
#include <mojo/core/state_tracker.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( test_state_tracker )
{

	StateTrackerSP st(new StateTracker());

	BOOST_REQUIRE(st);
}
