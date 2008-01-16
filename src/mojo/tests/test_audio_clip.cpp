
#define BOOST_TEST_MODULE mojo_audio_clip

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/filesystem.hpp>
#include <mojo/application.hpp>
#include <mojo/audio_clip.hpp>
#include <mojo/audio_clip_ptr.hpp>
#include <mojo/audio_file_ptr.hpp>

using namespace boost::unit_test;
using namespace mojo;

BOOST_AUTO_TEST_CASE( audio_clip )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	ApplicationSPtr app = Application::init (argc, argv);

	// given a file path create an AudioFile

	const fs::path path("share/test_files/mono-5sec-piano.wav");
	
	AudioFileSPtr audiofile = Application::open_audiofile (path);

	BOOST_REQUIRE(audiofile);
	
	// create a new AudioClip
	//AudioClipSPtr clip(new AudioClip(AudioFile));

	// The AudioClip has the same properties as the
	// AudioFile, file format, channel format, samplerate, length
	
	


}
