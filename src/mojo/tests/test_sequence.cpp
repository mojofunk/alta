#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_sequence
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

BOOST_AUTO_TEST_CASE(audio_sequence)
{
	AudioSequence seq;

	AudioEventSP ae1(new AudioEvent);

	BOOST_CHECK(seq.insert(ae1).second);
	BOOST_CHECK(seq.erase(ae1) == 1);
}
