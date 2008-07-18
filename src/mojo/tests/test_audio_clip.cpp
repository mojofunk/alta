
#define BOOST_TEST_MODULE mojo_audio_clip

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/filesystem.hpp>
#include <mojo/app.hpp>
#include <mojo/audio_clip.hpp>
#include <mojo/project_directory.hpp>

using namespace boost::unit_test;
using namespace mojo;

BOOST_AUTO_TEST_CASE( audio_clip )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);

	// given a file path create an AudioFile

	ProjectDirectory pdir("./share/projects/motronic");

	const fs::path file_path(pdir.audiofiles_path () / "notify.wav");
	
	AudioFileSPtr audiofile = App::open_audiofile (file_path);

	BOOST_REQUIRE(audiofile);
	
	// create a new AudioClip
	//AudioClipSPtr clip(new AudioClip(AudioFile));

	// The AudioClip has the same properties as the
	// AudioFile, file format, channel format, samplerate, length
}
