
#define BOOST_TEST_MODULE mojo_audio_driver_plugin

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include <mojo/forward.hpp>
#include <mojo/app.hpp>
#include <mojo/plugin.hpp>
#include <mojo/audio_driver_plugin.hpp>

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

int
callback (count_t frames)
{
	return AudioDevice::CONTINUE;
}

void
test_device (AudioDevice* dev)
{
	BOOST_REQUIRE(dev);

	AudioDevice::error_t err = dev->open (callback, 44100);

	BOOST_CHECK(err != AudioDevice::NO_ERROR);

	err = dev->close ();

	BOOST_CHECK(err != AudioDevice::NO_ERROR);
}

void
test_audio_driver_plugin (AudioDriverPluginSPtr plug)
{
	BOOST_REQUIRE(plug);

	BOOST_TEST_MESSAGE(plug->get_author());
	BOOST_TEST_MESSAGE(plug->get_description());
	BOOST_TEST_MESSAGE(plug->get_version());

	AudioDriverPlugin::Devices devices = plug->get_devices();

	BOOST_CHECK(!devices.empty());

	for_each (devices.begin(), devices.end(), test_device);
}

BOOST_AUTO_TEST_CASE( audio_driver_plugin_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AppSPtr app = App::init (argc, argv);
	BOOST_REQUIRE(app);

	AudioDriverPluginSet plugins = App::get_audio_driver_plugins();

	BOOST_CHECK(!plugins.empty());

	for_each (plugins.begin(), plugins.end(), test_audio_driver_plugin);
}
