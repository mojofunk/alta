
#ifndef PORTAUDIO_AUDIO_DRIVER_MODULE
#define PORTAUDIO_AUDIO_DRIVER_MODULE

#include "mojo-audio-driver.hpp"

namespace mojo {

class PortaudioAudioDriverModule : public AudioDriverModule
{
public: // constructors

	PortaudioAudioDriverModule();
	~PortaudioAudioDriverModule();

public: // Module interface

	virtual std::string get_author ();

	virtual std::string get_description ();

	virtual std::string get_version ();

public: // AudioDriverModule interface

	AudioDeviceSPSet get_devices () const;

private: // member data


};

} // namespace mojo

#endif
