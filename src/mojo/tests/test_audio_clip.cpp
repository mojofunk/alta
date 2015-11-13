#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_audio_clip
#endif

#include "test_includes.hpp"

#include "mojo-application.hpp"

BOOST_AUTO_TEST_CASE(audio_clip)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application::initialize();
	// given a file path create an AudioFile

	fs::path project_path;
	fs::path audiofile_path;

	BOOST_CHECK(find_directory_in_test_path("projects", project_path));

	project_path = project_path / "motronic";

	ProjectDirectory pdir(project_path);

	BOOST_CHECK(!pdir.is_valid());

	BOOST_CHECK(
	    find_matching_file(pdir.audiofiles_path(), "notify.wav", audiofile_path));

	BOOST_CHECK(is_regular_file(audiofile_path));

	AudioFileSP audiofile = Application::open_audiofile(audiofile_path);

	BOOST_REQUIRE(audiofile);

	// create a new AudioClip
	// AudioClipSP clip(new AudioClip(AudioFile));

	// The AudioClip has the same properties as the
	// AudioFile, file format, channel format, samplerate, length
	Application::deinitialize();
}
