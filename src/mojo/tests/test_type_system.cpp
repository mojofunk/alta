#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_type_system
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

template <class T>
bool
test_type_name(const string& type_name)
{
	return (types::get_type_name(typeid(T)) == type_name);
}

template <class T>
void
test_type_factory(const string& type_name)
{
	T* instance = boost::any_cast<T*>(types::create_type(type_name));

	BOOST_REQUIRE(instance);

	delete instance;
}

BOOST_AUTO_TEST_CASE(mojo_test_type_system)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application app;

	BOOST_CHECK(test_type_name<int32_t>(TypeNames::int32_type_name));
	BOOST_CHECK(test_type_name<int64_t>(TypeNames::int64_type_name));
	BOOST_CHECK(test_type_name<float>(TypeNames::float_type_name));
	BOOST_CHECK(test_type_name<string>(TypeNames::string_type_name));
	BOOST_CHECK(test_type_name<AudioTrack>(TypeNames::audio_track_type_name));
	BOOST_CHECK(test_type_name<MidiTrack>(TypeNames::midi_track_type_name));
	BOOST_CHECK(
	    test_type_name<AudioSequence>(TypeNames::audio_sequence_type_name));
	BOOST_CHECK(test_type_name<AudioEvent>(TypeNames::audio_event_type_name));

	BOOST_CHECK_NO_THROW(test_type_factory<int32_t>(TypeNames::int32_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<int64_t>(TypeNames::int64_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<float>(TypeNames::float_type_name));
	BOOST_CHECK_NO_THROW(test_type_factory<string>(TypeNames::string_type_name));
	BOOST_CHECK_NO_THROW(
	    test_type_factory<AudioTrack>(TypeNames::audio_track_type_name));
	BOOST_CHECK_NO_THROW(
	    test_type_factory<MidiTrack>(TypeNames::midi_track_type_name));
	BOOST_CHECK_NO_THROW(
	    test_type_factory<AudioSequence>(TypeNames::audio_sequence_type_name));
	BOOST_CHECK_NO_THROW(
	    test_type_factory<AudioEvent>(TypeNames::audio_event_type_name));
}
