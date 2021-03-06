MOJO_DEBUG_DOMAIN(PORTAUDIO_DRIVER)

PortaudioAudioDriver::PortaudioAudioDriver()
    : m_initialized(false)
{
	MOJO_DEBUG(PORTAUDIO_DRIVER);
	initialize();
}

PortaudioAudioDriver::~PortaudioAudioDriver()
{
	MOJO_DEBUG(PORTAUDIO_DRIVER);
	terminate();
}

AudioDeviceSPSet
PortaudioAudioDriver::get_devices() const
{
	AudioDeviceSPSet devices;
	discover_devices(devices);
	return devices;
}

bool
PortaudioAudioDriver::initialize()
{
	if (m_initialized) return true;

	PaError error = Pa_Initialize();
	if (error == paNoError) {
		return m_initialized = true;
	} else {
		MOJO_DEBUG_MSG(
		    PORTAUDIO_DRIVER,
		    compose("Unable to Initialize portaudio: %", Pa_GetErrorText(error)));
	}
	return false;
}

bool
PortaudioAudioDriver::terminate()
{
	if (!m_initialized) return true;

	PaError error = Pa_Terminate();
	if (error == paNoError) {
		return m_initialized = false;
	} else {
		MOJO_DEBUG_MSG(
		    PORTAUDIO_DRIVER,
		    compose("Unable to Terminate portaudio: %", Pa_GetErrorText(error)));
	}
	return false;
}

void
PortaudioAudioDriver::discover_devices(AudioDeviceSPSet& devices)
{
	int device_count = Pa_GetDeviceCount();

	if (device_count < 0) {
		MOJO_DEBUG_MSG(
		    PORTAUDIO_DRIVER,
		    compose("Invalid device count: %", Pa_GetErrorText(device_count)));
		return;
	}

	for (PaDeviceIndex i = 0; i < device_count; ++i) {
		AudioDeviceSP device(new PortaudioAudioDevice(i));
		devices.insert(device);
	}
}
