
#define BOOST_TEST_MODULE mojo_project

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/application.hpp>
#include <mojo/project.hpp>
#include <mojo/project_ptr.hpp>
#include <mojo/audio_track.hpp>
#include <mojo/audio_sequence.hpp>
#include <mojo/audio_event.hpp>

#include <glib.h>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

const string project_filename = "project1";

void
add_random_events (AudioSequenceSPtr aseq)
{
	int min_event_count = 1;
	int max_event_count = 100;
	int min_event_duration = 16;
	int max_event_duration = 65536;

	int num_events = g_random_int_range (min_event_count, max_event_count);

	for (int i = 0; i < num_events; ++i)
	{
		int event_position = g_random_int_range (1, 16777216);
		int event_duration = g_random_int_range (min_event_duration, max_event_duration);

		AudioEventSPtr new_event(new AudioEvent(event_position, event_duration));

		BOOST_REQUIRE(new_event);

		BOOST_CHECK(aseq->insert (new_event).second);
	}
}

BOOST_AUTO_TEST_CASE( save_open_project_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	ApplicationSPtr app = Application::create (argc, argv);

	ProjectSPtr proj(new Project);
	BOOST_REQUIRE(proj);
	
	BOOST_REQUIRE(proj->new_audio_track("Kick Drum"));
	BOOST_REQUIRE(proj->new_audio_track("High Hats"));
	BOOST_REQUIRE(proj->new_audio_track("Snare"));
	BOOST_REQUIRE(proj->new_audio_track("Bass Guitar"));
	BOOST_REQUIRE(proj->new_audio_track("Guitar"));
	BOOST_REQUIRE(proj->new_audio_track("Keyboard"));
	
	BOOST_REQUIRE(proj->new_midi_track("Synth Pad"));
	BOOST_REQUIRE(proj->new_midi_track("Drum Fill"));
	BOOST_REQUIRE(proj->new_midi_track("Horn"));

	Project::track_container_t tracks = proj->get_tracks ();

	BOOST_CHECK(tracks.size() == 9);

	for (Project::track_container_t::iterator i = tracks.begin();
			i != tracks.end(); ++i)
	{
		AudioTrackSPtr audio_track = boost::dynamic_pointer_cast<AudioTrack>(*i);

		if (audio_track)
		{
			add_random_events (audio_track->get_audio_sequence ());
		}
	}

	// don't need to set project directory to save as no media
	// has been recorded or imported etc.

	// try to save project using project filename in current directory  

	BOOST_CHECK_NO_THROW(proj->save_as("", project_filename));

}
