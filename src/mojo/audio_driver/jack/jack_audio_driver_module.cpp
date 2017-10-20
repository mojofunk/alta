
#include "jack_audio_driver_module.hpp"

JACKAudioDriverModule::JACKAudioDriverModule()
{
}

JACKAudioDriverModule::~JACKAudioDriverModule()
{
}

std::string
JACKAudioDriverModule::get_author()
{
	return "Tim Mayberry";
}

std::string
JACKAudioDriverModule::get_description()
{
	return "JACK module";
}

std::string
JACKAudioDriverModule::get_version()
{
	return "0.0.1";
}

AudioDeviceSPSet
JACKAudioDriverModule::get_devices() const
{
	return AudioDeviceSPSet();
}

MOJO_CAPI void*
mojo_module_factory(void)
{
	return new JACKAudioDriverModule;
}
