#include "mojo-portmidi-midi-driver.hpp"

MOJO_DEBUG_DOMAIN(PORTMIDI_DEVICE)

namespace mojo {

PortmidiMIDIDevice::PortmidiMIDIDevice(PmDeviceID id)
    : m_id(id)
{
}

PortmidiMIDIDevice::~PortmidiMIDIDevice() {}

std::string PortmidiMIDIDevice::get_name() const
{
	return get_device_info()->name;
}

PmDeviceInfo const* PortmidiMIDIDevice::get_device_info() const
{
	return Pm_GetDeviceInfo(m_id);
}

} // namespace mojo
