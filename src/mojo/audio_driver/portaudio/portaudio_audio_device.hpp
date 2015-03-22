
#ifndef PORTAUDIO_AUDIO_DEVICE
#define PORTAUDIO_AUDIO_DEVICE

#include <mojo-portaudio-audio-driver.hpp>

namespace mojo {

class PortaudioAudioDevice : public AudioDevice
{
public: // Constructors

	PortaudioAudioDevice (PaDeviceIndex);
	~PortaudioAudioDevice ();

public: // AudioDevice interface

	virtual std::string get_name () const;

	virtual error_t open (uint32_t input_channels,
	                      uint32_t output_channels,
	                      uint32_t samplerate,
	                      uint32_t buffersize,
	                      callback_t* cb);

	virtual error_t start ();

	virtual error_t stop ();

	virtual error_t close ();

	virtual channel_count_t max_input_channels () const;

	virtual channel_count_t max_output_channels () const;

	virtual samplerate_t get_default_samplerate () const;

	virtual void get_supported_samplerates (std::vector<samplerate_t>&) const;

private: // methods

	PaDeviceInfo const * get_device_info () const;

	PaStreamParameters get_default_input_params () const;

	PaStreamParameters get_default_output_params () const;

	static int portaudio_callback (
			const void *inputBuffer, void *outputBuffer,
			unsigned long framesPerBuffer,
			const PaStreamCallbackTimeInfo* timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData);

private: // member data

	PaDeviceIndex m_device_index;
	PaStream *    m_stream;

	float left_phase;
	float right_phase;

};

} // namespace mojo

#endif
