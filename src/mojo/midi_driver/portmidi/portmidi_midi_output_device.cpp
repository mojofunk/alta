#include "mojo-portmidi-midi-driver.hpp"

MOJO_DEBUG_DOMAIN(PORTMIDI_OUTPUT_DEVICE)

namespace mojo {

PortmidiMIDIOutputDevice::PortmidiMIDIOutputDevice(PmDeviceID id)
    : m_id(id)
    , m_stream(NULL)
{
}

PortmidiMIDIOutputDevice::~PortmidiMIDIOutputDevice() {}

std::string PortmidiMIDIOutputDevice::get_name() const
{
	return get_device_info()->name;
}

MIDIDevice::error_t PortmidiMIDIOutputDevice::open(time_callback_t* callback,
                                                   void* user_data)
{
	int latency = 0;
	int buffer_size = 1024;
	void* output_driver_info = NULL;
	PmError err = Pm_OpenOutput(&m_stream,
	                            m_id,
	                            output_driver_info,
	                            buffer_size,
	                            callback,
	                            user_data,
	                            latency);

	if (err != pmNoError) {
		MOJO_DEBUG_MSG(
		    PORTMIDI_OUTPUT_DEVICE,
		    compose("Unable to open output stream: %", Pm_GetErrorText(err)));
	}
	return (MIDIDevice::error_t)err;
}

MIDIDevice::error_t PortmidiMIDIOutputDevice::close()
{
	if (m_stream == NULL) return MIDIDevice::UNKNOWN_ERROR;

	PmError err = Pm_Close(m_stream);

	if (err != pmNoError) {
		MOJO_DEBUG_MSG(
		    PORTMIDI_OUTPUT_DEVICE,
		    compose("Unable to close output stream: %", Pm_GetErrorText(err)));
	}
	return (MIDIDevice::error_t)err;
}

std::string PortmidiMIDIOutputDevice::get_error_string(error_t err)
{
	return Pm_GetErrorText((PmError)err);
}

MIDIDevice::error_t PortmidiMIDIOutputDevice::write(Event* buffer, int32_t size)
{
	PmError err = Pm_Write(m_stream, (PmEvent*)buffer, size);

	if (err != pmNoError) {
		MOJO_DEBUG_MSG(PORTMIDI_OUTPUT_DEVICE,
		               compose("Unable to write to stream: %", Pm_GetErrorText(err)));
	}
	return (MIDIDevice::error_t)err;
}

PmDeviceInfo const* PortmidiMIDIOutputDevice::get_device_info() const
{
	return Pm_GetDeviceInfo(m_id);
}

} // namespace mojo
