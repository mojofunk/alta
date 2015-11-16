#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_audio_driver_module
#endif

#include "test_includes.hpp"

#include "mojo-audio-driver.hpp"
#include "mojo-application.hpp"

namespace {
float left_phase(0);
float right_phase(0);
}

AudioDevice::callback_result_t callback(const float* input_buffer,
                                        const float* output_buffer,
                                        count_t frames,
                                        void* user_data)
{
	BOOST_TEST_MESSAGE(compose("Test Callback: frames %", frames));

	float* out = (float*)output_buffer;

	BOOST_REQUIRE(out);

	unsigned int i;
	(void)input_buffer;
	for (i = 0; i < frames; i++) {
		*out++ = left_phase;
		*out++ = right_phase;
		/* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
		left_phase += 0.01f;
		/* When signal reaches top, drop back down. */
		if (left_phase >= 1.0f) left_phase -= 2.0f;
		/* higher pitch so we can distinguish left and right. */
		right_phase += 0.03f;
		if (right_phase >= 1.0f) right_phase -= 2.0f;
	}
	return AudioDevice::CONTINUE;
}

void test_device(AudioDeviceSP dev)
{
	BOOST_REQUIRE(dev);

	uint32_t buffersize = 1024;

	if (dev->max_output_channels() < 2) {
		BOOST_TEST_MESSAGE(
		    compose("Device % has % outputs, at least 2 required for tests",
		            dev->get_name(),
		            dev->max_output_channels()));
		return;
	}

	AudioDevice::error_t err = dev->open(dev->max_input_channels(),
	                                     dev->max_output_channels(),
	                                     dev->get_default_samplerate(),
	                                     buffersize,
	                                     callback,
	                                     NULL);

	if (err != AudioDevice::NO_ERROR) {
		BOOST_TEST_MESSAGE(
		    compose("Unable to open device: %", dev->get_error_string(err)));
		return;
	}

	BOOST_CHECK(dev->is_open());

	err = dev->start();

	BOOST_CHECK(err == AudioDevice::NO_ERROR);
	BOOST_CHECK(dev->is_active());

	mojo::usleep(2 * 1000000);

	BOOST_TEST_MESSAGE(compose("Input Latency: %", dev->get_input_latency()));
	BOOST_TEST_MESSAGE(compose("Output Latency: %", dev->get_output_latency()));
	BOOST_TEST_MESSAGE(compose("CPU Load: %", dev->get_cpu_load()));

	err = dev->stop();

	BOOST_CHECK(err == AudioDevice::NO_ERROR);

	BOOST_CHECK(dev->is_stopped());

	err = dev->close();

	BOOST_CHECK(err == AudioDevice::NO_ERROR);

	BOOST_CHECK(!dev->is_open());
}

void print_device_info(AudioDeviceSP dev)
{
	BOOST_REQUIRE(dev);
	BOOST_TEST_MESSAGE(compose("Device name: %", dev->get_name()));
	BOOST_TEST_MESSAGE(
	    compose("Max Input Channels: %", dev->max_input_channels()));
	BOOST_TEST_MESSAGE(
	    compose("Max Output Channels: %", dev->max_output_channels()));
	BOOST_TEST_MESSAGE(
	    compose("Default Samplerate: %", dev->get_default_samplerate()));

	vector<samplerate_t> rates;
	dev->get_supported_samplerates(rates);

	ostringstream oss;
	for (auto const& rate : rates) {
		oss << " " << rate;
	}
	BOOST_TEST_MESSAGE(compose("Supported Samplerates: %", oss.str()));
}

void test_audio_driver_module(AudioDriverModuleSP mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());

	AudioDriverSP driver = mod->create_driver();
	AudioDeviceSPSet devices = driver->get_devices();

	BOOST_CHECK(!devices.empty());

	for_each(devices.begin(), devices.end(), print_device_info);
	for_each(devices.begin(), devices.end(), test_device);
}

BOOST_AUTO_TEST_CASE(audio_driver_module_test)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application app;
	AudioDriverModuleSPSet modules = Application::get_audio_driver_modules();

	BOOST_CHECK(!modules.empty());

	for_each(modules.begin(), modules.end(), test_audio_driver_module);
}
