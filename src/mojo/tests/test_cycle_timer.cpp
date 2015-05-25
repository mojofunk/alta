#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_cycle_timer
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/time/time.hpp"
#include "mojo/core/string/compose.hpp"
#include "mojo/core/audio/cycle_timer.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE(test_cycle_timer_basic)
{
	CycleTimer timer;

	timer.set_samplerate(48000);
	timer.set_samples_per_cycle(1024);

	for (int i = 0; i < 100; ++i) {
		uint64_t start_time = get_monotonic_time();
		uint64_t cycle_length = timer.get_length_us();

		timer.reset_start(start_time);

		mojo::usleep(cycle_length);

		uint64_t actual_length = timer.microseconds_since_start(get_monotonic_time());
		int64_t diff = actual_length - cycle_length;

		BOOST_TEST_MESSAGE(compose("Cycle length(us): %, predicted %, diff %",
		                           actual_length,
		                           cycle_length,
		                           diff));
	}
}
