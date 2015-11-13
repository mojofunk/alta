#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_project
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

const string project_filename = "project1";

void add_random_events(AudioSequenceSP aseq)
{
	int min_event_count = 1;
	int max_event_count = 100;
	int min_event_duration = 16;
	int max_event_duration = 65536;

	int num_events = g_random_int_range(min_event_count, max_event_count);

	for (int i = 0; i < num_events; ++i) {
		int event_position = g_random_int_range(1, 16777216);
		int event_duration =
		    g_random_int_range(min_event_duration, max_event_duration);

		AudioEventSP new_event(new AudioEvent(event_position, event_duration));

		BOOST_REQUIRE(new_event);

		BOOST_CHECK(aseq->insert(new_event).second);
	}
}

BOOST_AUTO_TEST_CASE(save_open_project_test)
{
	ProjectSP proj(new Project);
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

	TrackSPSet tracks = proj->get_tracks();

	BOOST_CHECK(tracks.size() == 9);

	for (auto& x : tracks) {
		AudioTrackSP audio_track = std::dynamic_pointer_cast<AudioTrack>(x);

		if (audio_track) {
			add_random_events(audio_track->get_audio_sequence());
		}
	}
}
