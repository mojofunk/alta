
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
//#include <mojo/filesystem_paths.hpp>

//#include <mojo/plugin_utils.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void
test_audiofile_plugin (AudioFilePluginSPtr plug)
{
	BOOST_REQUIRE(plug);

	BOOST_TEST_MESSAGE(plug->get_author());
	BOOST_TEST_MESSAGE(plug->get_description());
	BOOST_TEST_MESSAGE(plug->get_version());

	AudioFile* af = plug->create();

	BOOST_REQUIRE(af);

	AudioFileFormat* format = af->format();

	BOOST_REQUIRE(format);

	BOOST_TEST_MESSAGE(format->name());
	BOOST_TEST_MESSAGE(format->extension());

	delete af;
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
