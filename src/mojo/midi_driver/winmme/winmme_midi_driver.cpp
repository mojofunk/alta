MOJO_DEBUG_DOMAIN(WINMME_DRIVER);

WinMMEMIDIDriver::WinMMEMIDIDriver()
    : m_initialized(false)
{
	MOJO_DEBUG(WINMME_DRIVER);
	initialize();
	refresh_devices();
}

WinMMEMIDIDriver::~WinMMEMIDIDriver()
{
	MOJO_DEBUG(WINMME_DRIVER);
	terminate();
}

MIDIInputDeviceSPSet
WinMMEMIDIDriver::get_input_devices()
{
	return m_inputs;
}

MIDIOutputDeviceSPSet
WinMMEMIDIDriver::get_output_devices()
{
	return m_outputs;
}

bool
WinMMEMIDIDriver::initialize()
{
	if (m_initialized) return true;
	// TODO
	return false;
}

bool
WinMMEMIDIDriver::terminate()
{
	if (!m_initialized) return true;

	// TODO
	return false;
}

void
WinMMEMIDIDriver::refresh_devices()
{
	// TODO
}
