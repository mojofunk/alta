
#define BOOST_TEST_MODULE mojo_audio_driver_module

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/string/compose.hpp"

#include "mojo/audio_driver/mojo-audio-driver.hpp"

#include "mojo/application/application.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

int
callback (const float* input_buffer,
          const float* output_buffer,
          count_t frames,
          void* user_data)
{
	BOOST_TEST_MESSAGE(compose ("Test Callback: frames %", frames));
	return AudioDevice::CONTINUE;
}

void
test_device (AudioDeviceSP dev)
{
	BOOST_REQUIRE(dev);

	uint32_t buffersize = 1024;

	AudioDevice::error_t err = dev->open (dev->max_input_channels(),
	                                      dev->max_output_channels(),
	                                      dev->get_default_samplerate(),
										  buffersize,
	                                      callback);

	BOOST_CHECK(err == AudioDevice::NO_ERROR);

	err = dev->start ();

	BOOST_CHECK(err == AudioDevice::NO_ERROR);

	usleep(1000*10);

	err = dev->stop ();

	BOOST_CHECK(err == AudioDevice::NO_ERROR);

	err = dev->close ();

	BOOST_CHECK(err == AudioDevice::NO_ERROR);
}

void
print_device_info (AudioDeviceSP dev)
{
	BOOST_REQUIRE(dev);
	BOOST_TEST_MESSAGE(compose ("Device name: %", dev->get_name()));
	BOOST_TEST_MESSAGE(compose ("Max Input Channels: %", dev->max_input_channels()));
	BOOST_TEST_MESSAGE(compose ("Max Output Channels: %", dev->max_output_channels()));
	BOOST_TEST_MESSAGE(compose ("Default Samplerate: %", dev->get_default_samplerate()));

	vector<samplerate_t> rates;
	dev->get_supported_samplerates (rates);

	ostringstream oss;
	for (auto const& rate : rates) {
		oss << " " << rate;
	}
	BOOST_TEST_MESSAGE(compose ("Supported Samplerates: %", oss.str()));
}

void
test_audio_driver_module (AudioDriverModuleSP mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());

	AudioDriverSP driver = mod->create_driver();
	AudioDeviceSPSet devices = driver->get_devices();

	BOOST_CHECK(!devices.empty());

	for_each (devices.begin(), devices.end(), print_device_info);
	for_each (devices.begin(), devices.end(), test_device);
}

BOOST_AUTO_TEST_CASE( audio_driver_module_test )
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	AudioDriverModuleSPSet modules = Application::get_audio_driver_modules();

	BOOST_CHECK(!modules.empty());

	for_each (modules.begin(), modules.end(), test_audio_driver_module);
}
