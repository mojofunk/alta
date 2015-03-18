
#include "portaudio_audio_driver_module.hpp"

MOJO_DEBUG_DOMAIN(PORTAUDIO_DRIVER)

namespace mojo {

PortaudioAudioDriverModule::PortaudioAudioDriverModule ()
{
	MOJO_DEBUG(PORTAUDIO_DRIVER);
}

PortaudioAudioDriverModule::~PortaudioAudioDriverModule ()
{
	MOJO_DEBUG(PORTAUDIO_DRIVER);
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
	return AudioDeviceSPSet();
}

MOJO_CAPI void * mojo_module_factory(void)
{
	return new PortaudioAudioDriverModule;
}

} // namespace mojo
