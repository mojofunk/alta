
#define BOOST_TEST_MODULE mojo_audio_effect

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/forward.hpp>
#include <mojo/app.hpp>
#include <mojo/audio_effect_plugin.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

void
test_audio_effect_plugin (AudioEffectPluginSPtr plug)
{
	BOOST_REQUIRE(plug);

	BOOST_TEST_MESSAGE(plug->get_author());
	BOOST_TEST_MESSAGE(plug->get_description());
	BOOST_TEST_MESSAGE(plug->get_version());
}

BOOST_AUTO_TEST_CASE( test_audio_effect_plugins )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);
	BOOST_REQUIRE(app);

	AudioEffectPluginSet plugins = App::get_audio_effect_plugins ();

	BOOST_CHECK(!plugins.empty());

	for_each (plugins.begin(), plugins.end(), test_audio_effect_plugin);
}
