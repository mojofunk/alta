#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_audition
#endif

#include "test_includes.hpp"

// not sure exactly what headers will be needed atm
#include "mojo-application.hpp"
#include "mojo-audio-file.hpp"

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
