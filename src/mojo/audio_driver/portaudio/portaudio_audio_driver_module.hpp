
#ifndef PORTAUDIO_AUDIO_DRIVER_MODULE
#define PORTAUDIO_AUDIO_DRIVER_MODULE

#include <mojo-portaudio-audio-driver.hpp>

class PortaudioAudioDriverModule : public AudioDriverModule
{
public: // constructors
	PortaudioAudioDriverModule();
	~PortaudioAudioDriverModule();

public: // Module interface
	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // AudioDriverModule interface
	AudioDriverSP create_driver() const;
};

#endif
