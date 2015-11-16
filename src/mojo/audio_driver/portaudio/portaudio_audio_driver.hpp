#ifndef PORTAUDIO_AUDIO_DRIVER_H
#define PORTAUDIO_AUDIO_DRIVER_H

namespace mojo {

class PortaudioAudioDriver : public AudioDriver {
public: // constructors
	PortaudioAudioDriver();
	~PortaudioAudioDriver();

public: // AudioDriver interface
	AudioDeviceSPSet get_devices() const;

private: // methods
	bool initialize();
	bool terminate();

	static void discover_devices(AudioDeviceSPSet& devices);

private: // member data
	bool m_initialized;
};

} // namespace mojo

#endif
