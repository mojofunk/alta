
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

}

void test_device(MIDIDeviceSP dev) { BOOST_REQUIRE(dev); }

void print_device_info(MIDIDeviceSP dev)
{
	BOOST_REQUIRE(dev);
	BOOST_TEST_MESSAGE(compose("Device name: %", dev->get_name()));
	BOOST_TEST_MESSAGE(compose("Input device: %", dev->is_input()));
	BOOST_TEST_MESSAGE(compose("Output device: %", dev->is_output()));
}

void test_midi_driver_module(MIDIDriverModuleSP mod)
{
	BOOST_REQUIRE(mod);

	BOOST_TEST_MESSAGE(mod->get_author());
	BOOST_TEST_MESSAGE(mod->get_description());
	BOOST_TEST_MESSAGE(mod->get_version());

	MIDIDriverSP driver = mod->create_driver();
	MIDIDeviceSPSet devices = driver->get_devices();

	BOOST_CHECK(!devices.empty());

	for_each(devices.begin(), devices.end(), print_device_info);
	for_each(devices.begin(), devices.end(), test_device);
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
