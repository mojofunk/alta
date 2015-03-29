
#include "mojo-portmidi-midi-driver.hpp"

MOJO_DEBUG_DOMAIN(PORTMIDI_DRIVER);

namespace mojo {

PortmidiMIDIDriver::PortmidiMIDIDriver()
    : m_initialized(false)
{
	MOJO_DEBUG(PORTMIDI_DRIVER);
	initialize();
}

PortmidiMIDIDriver::~PortmidiMIDIDriver()
{
	MOJO_DEBUG(PORTMIDI_DRIVER);
	terminate();
}

MIDIDeviceSPSet PortmidiMIDIDriver::get_devices() const
{
	MIDIDeviceSPSet devices;
	discover_devices(devices);
	return devices;
}

bool PortmidiMIDIDriver::initialize()
{
	if (m_initialized) return true;

	PmError error = Pm_Initialize();
	if (error == pmNoError) {
		return m_initialized = true;
	} else {
		MOJO_DEBUG_MSG(
		    PORTMIDI_DRIVER,
		    compose("Unable to Initialize portmidi: %", Pm_GetErrorText(error)));
	}
	return false;
}

bool PortmidiMIDIDriver::terminate()
{
	if (!m_initialized) return true;

	PmError error = Pm_Terminate();
	if (error == pmNoError) {
		return m_initialized = false;
	} else {
		MOJO_DEBUG_MSG(
		    PORTMIDI_DRIVER,
		    compose("Unable to Terminate portmidi: %", Pm_GetErrorText(error)));
	}
	return false;
}

void PortmidiMIDIDriver::discover_devices(MIDIDeviceSPSet& devices)
{
	int device_count = Pm_CountDevices();

	for (PmDeviceID i = 0; i < device_count; ++i) {
		MIDIDeviceSP device(new PortmidiMIDIDevice(i));
		devices.insert(device);
	}
}

} // namespace mojo
