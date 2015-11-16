MOJO_DEBUG_DOMAIN(PORTMIDI_INPUT_DEVICE)

namespace mojo {

PortmidiMIDIInputDevice::PortmidiMIDIInputDevice(PmDeviceID id)
    : m_id(id)
    , m_stream(NULL)
{
}

PortmidiMIDIInputDevice::~PortmidiMIDIInputDevice()
{
}

std::string PortmidiMIDIInputDevice::get_name() const
{
	return get_device_info()->name;
}

MIDIDevice::error_t PortmidiMIDIInputDevice::open(time_callback_t* callback,
                                                  void* user_data)
{
	PmError err = Pm_OpenInput(&m_stream, m_id, NULL, 1024, callback, user_data);

	if (err != pmNoError) {
		MOJO_DEBUG_MSG(
		    PORTMIDI_INPUT_DEVICE,
		    compose("Unable to open input stream: %", Pm_GetErrorText(err)));
	}
	return (MIDIDevice::error_t)err;
}

MIDIDevice::error_t PortmidiMIDIInputDevice::close()
{
	if (m_stream == NULL) return MIDIDevice::UNKNOWN_ERROR;

	PmError err = Pm_Close(m_stream);

	if (err != pmNoError) {
		MOJO_DEBUG_MSG(
		    PORTMIDI_INPUT_DEVICE,
		    compose("Unable to close input stream: %", Pm_GetErrorText(err)));
	}
	return (MIDIDevice::error_t)err;
}

std::string PortmidiMIDIInputDevice::get_error_string(error_t err)
{
	return Pm_GetErrorText((PmError)err);
}

uint32_t PortmidiMIDIInputDevice::read(Event* buffer, int32_t size)
{
	int read = Pm_Read(m_stream, (PmEvent*)buffer, size);

	if (read < 0) {
		MOJO_DEBUG_MSG(PORTMIDI_INPUT_DEVICE,
		               compose("Unable to read from input stream: %",
		                       Pm_GetErrorText((PmError)read)));
		read = 0;
	}
	return read;
}

PmDeviceInfo const* PortmidiMIDIInputDevice::get_device_info() const
{
	return Pm_GetDeviceInfo(m_id);
}

} // namespace mojo
