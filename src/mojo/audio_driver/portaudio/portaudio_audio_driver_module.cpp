
#include <mojo-portaudio-audio-driver.hpp>

namespace mojo {

PortaudioAudioDriverModule::PortaudioAudioDriverModule() {}

PortaudioAudioDriverModule::~PortaudioAudioDriverModule() {}

std::string PortaudioAudioDriverModule::get_author() { return "Tim Mayberry"; }

std::string PortaudioAudioDriverModule::get_description()
{
	return "Portaudio module";
}

std::string PortaudioAudioDriverModule::get_version() { return "0.0.1"; }

AudioDriverSP PortaudioAudioDriverModule::create_driver() const
{
	return AudioDriverSP(new PortaudioAudioDriver);
}

MOJO_CAPI void* mojo_module_factory(void)
{
	return new PortaudioAudioDriverModule;
}

} // namespace mojo
