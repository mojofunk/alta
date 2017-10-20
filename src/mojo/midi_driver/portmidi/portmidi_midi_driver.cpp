MOJO_DEBUG_DOMAIN(PORTMIDI_DRIVER);

PortmidiMIDIDriver::PortmidiMIDIDriver()
    : m_initialized(false)
{
	MOJO_DEBUG(PORTMIDI_DRIVER);
	initialize();
	refresh_devices();
}

PortmidiMIDIDriver::~PortmidiMIDIDriver()
{
	MOJO_DEBUG(PORTMIDI_DRIVER);
	terminate();
}

MIDIInputDeviceSPSet
PortmidiMIDIDriver::get_input_devices()
{
	return m_inputs;
}

MIDIOutputDeviceSPSet
PortmidiMIDIDriver::get_output_devices()
{
	return m_outputs;
}

bool
PortmidiMIDIDriver::initialize()
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

bool
PortmidiMIDIDriver::terminate()
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

void
PortmidiMIDIDriver::refresh_devices()
{
	int device_count = Pm_CountDevices();

	// clear devices? or
	// remove devices no longer present?
	// what about devices in use?

	for (PmDeviceID i = 0; i < device_count; ++i) {
		const PmDeviceInfo* info = Pm_GetDeviceInfo(i);

		if (info == NULL) { // assert?
			MOJO_DEBUG_MSG(PORTMIDI_DRIVER, "Unable to get device info");
			continue;
		}

		if (info->input) {
			MIDIInputDeviceSP device(new PortmidiMIDIInputDevice(i));
			m_inputs.insert(device);
		} else if (info->output) {
			MIDIOutputDeviceSP device(new PortmidiMIDIOutputDevice(i));
			m_outputs.insert(device);
		} else { // assert?
			MOJO_DEBUG_MSG(PORTMIDI_DRIVER,
			               "Midi device neither input or output device");
		}
	}
}
