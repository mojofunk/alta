
#ifndef PORTAUDIO_AUDIO_DEVICE
#define PORTAUDIO_AUDIO_DEVICE

#include <mojo-portaudio-audio-driver.hpp>

namespace mojo {

class PortaudioAudioDevice : public AudioDevice {
public: // Constructors
	PortaudioAudioDevice(PaDeviceIndex);
	~PortaudioAudioDevice();

public: // AudioDevice interface
	virtual std::string get_name() const;

	virtual error_t open(uint32_t input_channels,
	                     uint32_t output_channels,
	                     uint32_t samplerate,
	                     uint32_t buffersize,
	                     callback_t* cb,
	                     void* user_data);

	virtual error_t start();

	virtual error_t stop();

	virtual error_t close();

	virtual std::string get_error_string(error_t);

	virtual channel_count_t max_input_channels() const;

	virtual channel_count_t max_output_channels() const;

	virtual samplerate_t get_default_samplerate() const;

	virtual void get_supported_samplerates(std::vector<samplerate_t>&) const;

private: // methods
	PaDeviceInfo const* get_device_info() const;

	PaStreamParameters get_default_input_params() const;

	PaStreamParameters get_default_output_params() const;

	static int portaudio_callback(const void* input_buffer,
	                              void* output_buffer,
	                              unsigned long frames_per_buffer,
	                              const PaStreamCallbackTimeInfo* time_info,
	                              PaStreamCallbackFlags status_flags,
	                              void* user_data);

private: // member data
	PaDeviceIndex m_device_index;
	PaStream* m_stream;

	callback_t* m_callback;
	void* m_user_data;
};

} // namespace mojo

#endif
