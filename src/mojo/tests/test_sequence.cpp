#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_sequence
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/application/audio_sequence.hpp"
#include "mojo/application/audio_event.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE(audio_sequence)
{
	AudioSequence seq;

	AudioEventSP ae1(new AudioEvent);

	BOOST_CHECK(seq.insert(ae1).second);
	BOOST_CHECK(seq.erase(ae1) == 1);
}
