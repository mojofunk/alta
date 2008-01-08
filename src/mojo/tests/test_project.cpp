
#define BOOST_TEST_MODULE mojo_project

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

#include <mojo/project.hpp>
#include <mojo/project_ptr.hpp>
#include <mojo/audio_track.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

const string project_filename = "project1";

BOOST_AUTO_TEST_CASE( save_open_project_test )
{
	ProjectSPtr proj = ProjectSPtr(new Project);
	BOOST_REQUIRE(proj);

	// create AudioTrack and add to project
	AudioTrackSPtr track1 = AudioTrackSPtr(new AudioTrack);
	BOOST_REQUIRE(track1);

	BOOST_CHECK(proj->add_audio_track(track1));
	BOOST_CHECK(!proj->add_audio_track(track1));

	// should be in a separate test case
	const string track_name = "Bass Guitar";

	track1->set_name(track_name);
	BOOST_CHECK_EQUAL(track1->get_name(), track_name);

	// don't need to set project directory to save as no media
	// has been recorded or imported etc.

	// try to save project using project filename in current directory  

	BOOST_CHECK_NO_THROW(proj->save_as("", project_filename));

}
