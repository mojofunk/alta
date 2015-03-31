
#define BOOST_TEST_MODULE mojo_midi_driver_module

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
//#include <boost/test/test_tools.hpp>

// for command line args
#include <boost/test/framework.hpp>

#include "mojo/core/string/compose.hpp"

#include "mojo/midi_driver/mojo-midi-driver.hpp"

#include "mojo/application/application.hpp"

using namespace boost::unit_test;
using namespace std;
using namespace mojo;

namespace {

MIDIDevice::timestamp_t midi_time_callback(void* user_data)
{
	static MIDIDevice::timestamp_t time = mojo::get_monotonic_time() / 1000;

	time = get_monotonic_time() / 1000;
	BOOST_TEST_MESSAGE(compose("midi_time_callback time : %", time));
	return time;
}
}

void test_input_device(MIDIDeviceSP dev)
{
	BOOST_REQUIRE(dev);

	MIDIInputDeviceSP input_dev = dynamic_pointer_cast<MIDIInputDevice>(dev);

	BOOST_REQUIRE(input_dev);

	MIDIDevice::error_t err = input_dev->open(midi_time_callback, NULL);

	BOOST_CHECK(err == MIDIDevice::NO_ERROR);

	if (err != MIDIDevice::NO_ERROR) {
		BOOST_TEST_MESSAGE(compose("Unable to open input device: %",
		                           input_dev->get_error_string(err)));
		return;
	}

	mojo::usleep(2 * 1000000);

	err = input_dev->close();

	BOOST_CHECK(err == MIDIDevice::NO_ERROR);

	if (err != MIDIDevice::NO_ERROR) {
		BOOST_TEST_MESSAGE(compose("Unable to close input device: %",
		                           input_dev->get_error_string(err)));
		return;
	}
}

void test_output_device(MIDIDeviceSP dev)
{
	BOOST_REQUIRE(dev);

	MIDIOutputDeviceSP output_dev = dynamic_pointer_cast<MIDIOutputDevice>(dev);

	BOOST_REQUIRE(output_dev);

	MIDIDevice::error_t err = output_dev->open(midi_time_callback, NULL);

	BOOST_CHECK(err == MIDIDevice::NO_ERROR);

	if (err != MIDIDevice::NO_ERROR) {
		BOOST_TEST_MESSAGE(compose("Unable to open output device: %",
		                           output_dev->get_error_string(err)));
		return;
	}

	mojo::usleep(2 * 1000000);

	err = output_dev->close();

	BOOST_CHECK(err == MIDIDevice::NO_ERROR);

	if (err != MIDIDevice::NO_ERROR) {
		BOOST_TEST_MESSAGE(compose("Unable to close output device: %",
		                           output_dev->get_error_string(err)));
		return;
	}
}

void print_input_device_info(MIDIInputDeviceSP input_dev)
{
	BOOST_REQUIRE(input_dev);
	BOOST_TEST_MESSAGE(compose("Input Device name: %", input_dev->get_name()));
}

void print_output_device_info(MIDIOutputDeviceSP output_dev)
{
	BOOST_REQUIRE(output_dev);
	BOOST_TEST_MESSAGE(compose("Output Device name: %", output_dev->get_name()));
}

void test_midi_driver_module(MIDIDriverModuleSP mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());

	MIDIDriverSP driver = mod->create_driver();
	MIDIInputDeviceSPSet input_devices = driver->get_input_devices();

	BOOST_CHECK(!input_devices.empty());

	BOOST_TEST_MESSAGE(compose("Input device count: %", input_devices.size()));

	for_each(input_devices.begin(), input_devices.end(), print_input_device_info);
	for_each(input_devices.begin(), input_devices.end(), test_input_device);

	MIDIOutputDeviceSPSet output_devices = driver->get_output_devices();

	BOOST_CHECK(!output_devices.empty());
	BOOST_TEST_MESSAGE(compose("Output device count: %", output_devices.size()));

	for_each(
	    output_devices.begin(), output_devices.end(), print_output_device_info);
	for_each(output_devices.begin(), output_devices.end(), test_output_device);
}

BOOST_AUTO_TEST_CASE(midi_driver_module_test)
{
	int argc = framework::master_test_suite().argc;
	char** argv = framework::master_test_suite().argv;

	Application::initialize();
	MIDIDriverModuleSPSet modules = Application::get_midi_driver_modules();

	BOOST_CHECK(!modules.empty());

	for_each(modules.begin(), modules.end(), test_midi_driver_module);
	Application::deinitialize();
}
