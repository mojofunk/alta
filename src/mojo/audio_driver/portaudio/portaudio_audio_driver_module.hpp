
#ifndef PORTAUDIO_AUDIO_DRIVER_MODULE
#define PORTAUDIO_AUDIO_DRIVER_MODULE

#include <mojo-portaudio-audio-driver.hpp>

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

private: // methods

	bool initialize ();
	bool terminate ();

	static void discover_devices (AudioDeviceSPSet& devices);

private: // member data

	bool m_initialized;
};

} // namespace mojo

#endif
