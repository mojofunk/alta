#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_audition
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include <mojo/mojo-internal.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE(audition_test)
{
	/*
	 * A Application is needed to audition an audio file
	 *
	 * Auditioning can occur while the transport is rolling
	 * or stopped.
	 *
	 * The volume of auditioning must be able to be controlled.
	 *
	 * Several audio files can be auditioned simultaneously.
	 *
	 * Each audition request must be able to be:
	 *	cancelled
	 *	playback stopped/started
	 *	repositioned
	 *
	 */
}
