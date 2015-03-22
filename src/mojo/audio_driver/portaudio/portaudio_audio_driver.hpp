
#ifndef PORTAUDIO_AUDIO_DRIVER
#define PORTAUDIO_AUDIO_DRIVER

#include <mojo-portaudio-audio-driver.hpp>

namespace mojo {

class PortaudioAudioDriver : public AudioDriver
{
public: // constructors

	PortaudioAudioDriver();
	~PortaudioAudioDriver();

public: // AudioDriver interface

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
