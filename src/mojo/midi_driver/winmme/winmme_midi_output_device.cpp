MOJO_DEBUG_DOMAIN(WINMME_OUTPUT_DEVICE)

namespace mojo {

WinMMEMIDIOutputDevice::WinMMEMIDIOutputDevice(/* TODO */)
{
}

WinMMEMIDIOutputDevice::~WinMMEMIDIOutputDevice()
{
}

std::string WinMMEMIDIOutputDevice::get_name() const
{
	// TODO
	return string();
}

MIDIDevice::error_t WinMMEMIDIOutputDevice::open(time_callback_t* callback,
                                                 void* user_data)
{
	// TODO
}

MIDIDevice::error_t WinMMEMIDIOutputDevice::close()
{
	// TODO
}

std::string WinMMEMIDIOutputDevice::get_error_string(error_t err)
{
	// TODO
}

MIDIDevice::error_t WinMMEMIDIOutputDevice::write(Event* buffer, int32_t size)
{
	// TODO
}

} // namespace mojo
