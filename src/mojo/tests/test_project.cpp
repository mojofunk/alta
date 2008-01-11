
#define BOOST_TEST_MODULE mojo_project

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/application.hpp>
#include <mojo/project.hpp>
#include <mojo/project_ptr.hpp>
#include <mojo/audio_track.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

const string project_filename = "project1";

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

	// don't need to set project directory to save as no media
	// has been recorded or imported etc.

	// try to save project using project filename in current directory  

	BOOST_CHECK_NO_THROW(proj->save_as("", project_filename));

}
