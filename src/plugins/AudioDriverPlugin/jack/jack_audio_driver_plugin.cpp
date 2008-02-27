
#include "jack_audio_driver_plugin.hpp"

#include <mojo/export.h>

namespace mojo {

JACKAudioDriverPlugin::JACKAudioDriverPlugin ()
{
}

JACKAudioDriverPlugin::~JACKAudioDriverPlugin ()
{
}

std::string
JACKAudioDriverPlugin::get_author()
{
	return "Tim Mayberry";
}

std::string
JACKAudioDriverPlugin::get_description()
{
	return "JACK plugin";
}

std::string
JACKAudioDriverPlugin::get_version()
{
	return "0.0.1";
}

AudioDriverPlugin::Devices
JACKAudioDriverPlugin::get_devices () const
{
	return Devices();
}

MOJO_CAPI void * mojo_plugin_factory(void)
{
	return new JACKAudioDriverPlugin;
}

} // namespace mojo
