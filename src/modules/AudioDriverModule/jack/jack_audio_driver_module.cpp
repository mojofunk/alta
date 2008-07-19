
#include "jack_audio_driver_module.hpp"

#include <mojo/export.h>

namespace mojo {

JACKAudioDriverModule::JACKAudioDriverModule () { }

JACKAudioDriverModule::~JACKAudioDriverModule () { }

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

AudioDeviceSet
JACKAudioDriverModule::get_devices () const
{
	return AudioDeviceSet();
}

MOJO_CAPI void * mojo_module_factory(void)
{
	return new JACKAudioDriverModule;
}

} // namespace mojo
