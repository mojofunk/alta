
#ifndef JACK_AUDIO_DEVICE
#define JACK_AUDIO_DEVICE

#include <mojo/mojo-internal.hpp>

namespace mojo {

class JackAudioDevice : public AudioDevice
{
public: // Constructors

        JackAudioDevice ();
        ~JackAudioDevice ();

public: // AudioDevice interface

	virtual error_t open (callback_t* cb,
			samplerate_t samplerate);

	virtual error_t close ();

};

} // namespace mojo

#endif
