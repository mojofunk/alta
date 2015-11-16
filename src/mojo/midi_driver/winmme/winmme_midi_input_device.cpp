MOJO_DEBUG_DOMAIN(WINMME_INPUT_DEVICE)

namespace mojo {

WinMMEMIDIInputDevice::WinMMEMIDIInputDevice(/* TODO */)
{
}

WinMMEMIDIInputDevice::~WinMMEMIDIInputDevice()
{
}

std::string WinMMEMIDIInputDevice::get_name() const
{
	// TODO
	return string();
}

MIDIDevice::error_t WinMMEMIDIInputDevice::open(time_callback_t* callback,
                                                void* user_data)
{
	// TODO
}

MIDIDevice::error_t WinMMEMIDIInputDevice::close()
{
	// TODO
}

std::string WinMMEMIDIInputDevice::get_error_string(error_t err)
{
	// TODO
}

uint32_t WinMMEMIDIInputDevice::read(Event* buffer, int32_t size)
{
	// TODO
}

} // namespace mojo
