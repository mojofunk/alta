
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

	virtual error_t open (uint32_t input_channels,
	                      uint32_t output_channels,
	                      uint32_t samplerate,
	                      uint32_t buffersize,
	                      callback_t* cb);

	virtual error_t close ();

private:

	int m_device_num;
};

} // namespace mojo

#endif
