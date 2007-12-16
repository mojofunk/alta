#define BOOST_TEST_MODULE mojo_s11n

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/audio_sequence.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

BOOST_AUTO_TEST_CASE( audio_sequence_s11n )
{
	AudioSequence seq;

	AudioEventSPtr aevent1(new AudioEvent);

	seq.add (aevent1);

}
