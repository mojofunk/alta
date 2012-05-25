
#define BOOST_TEST_MODULE mojo_type_system

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

#include "mojo/app/app.hpp"
#include "mojo/app/type_names.hpp"

#include "mojo/project/audio_event.hpp"
#include "mojo/project/audio_sequence.hpp"
#include "mojo/project/audio_track.hpp"
#include "mojo/project/midi_track.hpp"

#include "mojo/typesystem/type_system.hpp"


using namespace boost::unit_test;
using namespace std;
using namespace mojo;

template <class T>
bool
test_type_name (const string& type_name)
{
	return (TypeSystem::get_type_name (typeid(T)) == type_name);
}

template <class T>
void
test_type_factory (const string& type_name)
{
	T* instance = boost::any_cast<T*>(TypeSystem::create_type(type_name));

	BOOST_REQUIRE(instance);

	delete instance;
}

BOOST_AUTO_TEST_CASE( mojo_test_type_system )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSP app = App::init (argc, argv);

	BOOST_CHECK(test_type_name<int32_t>(int32_type_name));
	BOOST_CHECK(test_type_name<int64_t>(int64_type_name));
	BOOST_CHECK(test_type_name<float>(float_type_name));
	BOOST_CHECK(test_type_name<string>(string_type_name));
	BOOST_CHECK(test_type_name<AudioTrack>(audio_track_type_name));
	BOOST_CHECK(test_type_name<MidiTrack>(midi_track_type_name));
	BOOST_CHECK(test_type_name<AudioSequence>(audio_sequence_type_name));
	BOOST_CHECK(test_type_name<AudioEvent>(audio_event_type_name));

	BOOST_CHECK_NO_THROW(test_type_factory<int32_t>(int32_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<int64_t>(int64_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<float>(float_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<string>(string_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<AudioTrack>(audio_track_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<MidiTrack>(midi_track_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<AudioSequence>(audio_sequence_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<AudioEvent>(audio_event_type_name));
}
