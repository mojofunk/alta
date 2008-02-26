
#ifndef JACK_AUDIO_DRIVER_PLUGIN_INCLUDED
#define JACK_AUDIO_DRIVER_PLUGIN_INCLUDED

#include <mojo/audio_driver_plugin.hpp>

namespace mojo {

class JACKAudioDriverPlugin : public AudioDriverPlugin
{
public: // constructors

	JACKAudioDriverPlugin();
	~JACKAudioDriverPlugin();

public: // Plugin interface

	virtual std::string get_author ();

	virtual std::string get_description ();

	virtual std::string get_version ();

public: // AudioDriverPlugin interface

	AudioDevices get_devices () const;

private: // member data


};

} // namespace mojo

#endif
