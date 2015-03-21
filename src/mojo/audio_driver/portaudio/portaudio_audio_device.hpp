
#ifndef PORTAUDIO_AUDIO_DEVICE
#define PORTAUDIO_AUDIO_DEVICE

#include <mojo-audio-driver.hpp>

#include "portaudio.h"

namespace mojo {

class PortaudioAudioDevice : public AudioDevice
{
public: // Constructors

	PortaudioAudioDevice (PaDeviceInfo const *);
	~PortaudioAudioDevice ();

public: // AudioDevice interface

	virtual std::string get_name () const;

	virtual error_t open (uint32_t input_channels,
	                      uint32_t output_channels,
	                      uint32_t samplerate,
	                      uint32_t buffersize,
	                      callback_t* cb);

	virtual error_t close ();

	virtual channel_count_t get_input_count () const;

	virtual channel_count_t get_output_count () const;

	virtual samplerate_t get_default_samplerate () const;

private:

	PaDeviceInfo const * const m_device_info;

};

} // namespace mojo

#endif
