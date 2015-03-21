
#include "portaudio_audio_driver_module.hpp"
#include "portaudio_audio_device.hpp"

MOJO_DEBUG_DOMAIN(PORTAUDIO_DRIVER)


namespace mojo {

PortaudioAudioDriverModule::PortaudioAudioDriverModule ()
	: m_initialized(false)
{
	MOJO_DEBUG(PORTAUDIO_DRIVER);
	initialize ();
}

PortaudioAudioDriverModule::~PortaudioAudioDriverModule ()
{
	MOJO_DEBUG(PORTAUDIO_DRIVER);
	terminate ();
}

std::string
PortaudioAudioDriverModule::get_author()
{
	return "Tim Mayberry";
}

std::string
PortaudioAudioDriverModule::get_description()
{
	return "Portaudio module";
}

std::string
PortaudioAudioDriverModule::get_version()
{
	return "0.0.1";
}

AudioDeviceSPSet
PortaudioAudioDriverModule::get_devices () const
{
	AudioDeviceSPSet devices;
	discover_devices (devices);
	return devices;
}

MOJO_CAPI void * mojo_module_factory(void)
{
	return new PortaudioAudioDriverModule;
}

bool
PortaudioAudioDriverModule::initialize ()
{
	if (m_initialized) return true;

	PaError error = Pa_Initialize();
	if (error == paNoError) {
		return m_initialized = true;
	} else {
		MOJO_DEBUG_MSG(PORTAUDIO_DRIVER,
			compose ("Unable to Initialize portaudio: %s",
				Pa_GetErrorText (error)));
	}
	return false;
}

bool
PortaudioAudioDriverModule::terminate ()
{
	if (!m_initialized) return true;

	PaError error = Pa_Terminate();
	if (error == paNoError) {
		return m_initialized = false;
	} else {
		MOJO_DEBUG_MSG(PORTAUDIO_DRIVER,
			compose ("Unable to Terminate portaudio: %s",
				Pa_GetErrorText (error)));
	}
	return false;
}


void
PortaudioAudioDriverModule::discover_devices (AudioDeviceSPSet& devices)
{
	int device_count = Pa_GetDeviceCount ();

	if (device_count < 0) {
		MOJO_DEBUG_MSG(PORTAUDIO_DRIVER,
			compose ("Invalid device count: %s",
				Pa_GetErrorText (device_count)));
		return;
	}

	for (PaDeviceIndex i = 0; i < device_count; ++i) {
		AudioDeviceSP device(new PortaudioAudioDevice(i));
		devices.insert (device);
	}
}

} // namespace mojo
