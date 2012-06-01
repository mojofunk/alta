
#define BOOST_TEST_MODULE mojo_audio_clip

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/fs/file_utils.hpp"
#include "mojo/fs/project_directory.hpp"

#include "mojo/api/application.hpp"

#include "test_common.hpp"

using namespace boost::unit_test;
using namespace mojo;

BOOST_AUTO_TEST_CASE( audio_clip )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	BOOST_CHECK_NO_THROW (Application::init (argc, argv));

	// given a file path create an AudioFile

	fs::path project_path;
	fs::path audiofile_path;

	SearchPath tsp = test_search_path();

	tsp.add_subdirectory_to_paths ("projects");
	tsp.add_subdirectory_to_paths ("motronic");
	
	project_path = tsp.get_paths().front();

	BOOST_TEST_MESSAGE(project_path);

	BOOST_CHECK(is_directory (project_path));

	ProjectDirectory pdir(project_path);

	BOOST_CHECK(!pdir.is_valid ());

	BOOST_CHECK(find_matching_file (pdir.audiofiles_path(), "notify.wav", audiofile_path));

	BOOST_CHECK(is_regular_file (audiofile_path));

	AudioFileSP audiofile = Application::open_audiofile (audiofile_path);

	BOOST_REQUIRE(audiofile);
	
	// create a new AudioClip
	//AudioClipSP clip(new AudioClip(AudioFile));

	// The AudioClip has the same properties as the
	// AudioFile, file format, channel format, samplerate, length

	Application::cleanup ();
}
