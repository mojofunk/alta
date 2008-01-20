
#define BOOST_TEST_MODULE mojo_plugin_utils

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/application.hpp>
#include <mojo/plugin.hpp>
#include <mojo/plugin_ptr.hpp>
#include <mojo/audio_file_plugin.hpp>
#include <mojo/audio_file_plugin_ptr.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void
test_audiofile_format (AudioFileFormat* format)
{
	BOOST_REQUIRE(format);

	BOOST_TEST_MESSAGE(format->name());
	BOOST_TEST_MESSAGE(format->extension());
}

void
test_open_file (AudioFilePluginSPtr plug)
{
	AudioFileSPtr af(plug->open("share/projects/motronic/audiofiles/notify.wav"));

	BOOST_REQUIRE(af);

	BOOST_CHECK_EQUAL(af->samplerate(), 22050U);
	BOOST_CHECK_EQUAL(af->channels(), 2U);

	test_audiofile_format (af->format());
}

void
test_audiofile_plugin (AudioFilePluginSPtr plug)
{
	BOOST_REQUIRE(plug);

	BOOST_TEST_MESSAGE(plug->get_author());
	BOOST_TEST_MESSAGE(plug->get_description());
	BOOST_TEST_MESSAGE(plug->get_version());

	test_open_file (plug);

	AudioFilePlugin::Formats formats(plug->get_readable_formats());

	BOOST_CHECK(!formats.empty());

	for_each (formats.begin(), formats.end(), test_audiofile_format);
}

BOOST_AUTO_TEST_CASE( audiofile_plugin_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	ApplicationSPtr app = Application::init (argc, argv);
	BOOST_REQUIRE(app);

	AudioFilePluginSet plugins = Application::get_audiofile_plugins();

	BOOST_CHECK(!plugins.empty());

	for_each (plugins.begin(), plugins.end(), test_audiofile_plugin);
}
