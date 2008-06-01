
#ifndef JACK_AUDIO_DRIVER_PLUGIN_INCLUDED
#define JACK_AUDIO_DRIVER_PLUGIN_INCLUDED

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
