#ifndef MOJO_SINGLE_TEST_EXE
#define BOOST_TEST_MODULE mojo_midi_driver_module
#endif

#include "test_includes.hpp"

#include "mojo-midi-driver.hpp"
#include "mojo-application.hpp"

namespace
{

MIDIDevice::timestamp_t
midi_time_callback(void* user_data)
{
	static MIDIDevice::timestamp_t time = mojo::get_monotonic_time() / 1000;

	time = get_monotonic_time() / 1000;
	BOOST_TEST_MESSAGE(compose("midi_time_callback time : %", time));
	return time;
}
}

void
test_input_device(MIDIDeviceSP dev)
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

void
test_output_device(MIDIDeviceSP dev)
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

	MIDIDevice::Event event;

	// Note On, Channel 1, Middle C, Vel 127
	event.message = 0x903C7F00;
	event.timestamp = 0; // ignored, sent immediately

	BOOST_TEST_MESSAGE("Sending Note On");

	output_dev->write(&event, 1);

	mojo::usleep(2 * 1000000);

	// Note Off, Channel 1, Middle C, Vel 0
	event.message = 0x803F0000;
	event.timestamp = 0; // ignored, sent immediately

	BOOST_TEST_MESSAGE("Sending Note Off");

	output_dev->write(&event, 1);

	mojo::usleep(1 * 1000000);

	err = output_dev->close();

	BOOST_CHECK(err == MIDIDevice::NO_ERROR);

	if (err != MIDIDevice::NO_ERROR) {
		BOOST_TEST_MESSAGE(compose("Unable to close output device: %",
		                           output_dev->get_error_string(err)));
		return;
	}
}

void
print_input_device_info(MIDIInputDeviceSP input_dev)
{
	BOOST_REQUIRE(input_dev);
	BOOST_TEST_MESSAGE(compose("Input Device name: %", input_dev->get_name()));
}

void
print_output_device_info(MIDIOutputDeviceSP output_dev)
{
	BOOST_REQUIRE(output_dev);
	BOOST_TEST_MESSAGE(compose("Output Device name: %", output_dev->get_name()));
}

void
test_midi_driver_module(MIDIDriverModuleSP mod)
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

	Application app;
	MIDIDriverModuleSPSet modules = Application::get_midi_driver_modules();

	BOOST_CHECK(!modules.empty());

	for_each(modules.begin(), modules.end(), test_midi_driver_module);
}
