
#ifndef PORTAUDIO_AUDIO_DEVICE
#define PORTAUDIO_AUDIO_DEVICE

#include <mojo-audio-driver.hpp>

namespace mojo {

class PortaudioAudioDevice : public AudioDevice
{
public: // Constructors

        PortaudioAudioDevice ();
        ~PortaudioAudioDevice ();

public: // AudioDevice interface

	virtual error_t open (callback_t* cb,
			samplerate_t samplerate);

	virtual error_t close ();

};

} // namespace mojo

#endif
