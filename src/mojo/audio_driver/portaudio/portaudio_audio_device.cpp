#include "portaudio_audio_device.hpp"

MOJO_DEBUG_DOMAIN(PORTAUDIO_DEVICE)

namespace mojo {

PortaudioAudioDevice::PortaudioAudioDevice (PaDeviceIndex index)
	: m_device_index(index)
	, m_stream(0)
	, left_phase(0)
	, right_phase(0)
{

}

PortaudioAudioDevice::~PortaudioAudioDevice ()
{


}

std::string
PortaudioAudioDevice::get_name () const
{
	return get_device_info()->name;
}

int
PortaudioAudioDevice::portaudio_callback (
		const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData)
{
	MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Portaudio Callback"));
	PortaudioAudioDevice* device = static_cast<PortaudioAudioDevice*>(userData);
	float *out = (float*)outputBuffer;
	unsigned int i;
	(void) inputBuffer;
	for( i=0; i<framesPerBuffer; i++ )
	{
		*out++ = device->left_phase;
		*out++ = device->right_phase;
		/* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
		device->left_phase += 0.01f;
		/* When signal reaches top, drop back down. */
		if( device->left_phase >= 1.0f ) device->left_phase -= 2.0f;
		/* higher pitch so we can distinguish left and right. */
		device->right_phase += 0.03f;
		if( device->right_phase >= 1.0f ) device->right_phase -= 2.0f;
	}
	return 0;
}

AudioDevice::error_t
PortaudioAudioDevice::open (uint32_t input_channels,
	                        uint32_t output_channels,
	                        uint32_t samplerate,
	                        uint32_t buffersize,
	                        callback_t* cb)
{
	PaError err = Pa_OpenDefaultStream(&m_stream,
	                                   0, // inputs
	                                   2, // outputs
	                                   paFloat32,
	                                   44100,
	                                   256,
	                                   portaudio_callback,
	                                   this);
	if(err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Opened audio stream"));
		return AudioDevice::NO_ERROR;
	} else {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Unable to open stream: %s",
				Pa_GetErrorText (err)));
	}
	return AudioDevice::UNKNOWN_ERROR;
}

AudioDevice::error_t
PortaudioAudioDevice::start ()
{
	PaError err = Pa_StartStream(m_stream);
	if(err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Started audio stream"));
		return AudioDevice::NO_ERROR;
	} else {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Unable to start stream: %s",
				Pa_GetErrorText (err)));
	}
	return AudioDevice::UNKNOWN_ERROR;
}

AudioDevice::error_t
PortaudioAudioDevice::stop ()
{
	PaError err = Pa_StopStream(m_stream);
	if(err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Stopped audio stream"));
		return AudioDevice::NO_ERROR;
	} else {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Unable to stop stream: %s",
				Pa_GetErrorText (err)));
	}
	return AudioDevice::UNKNOWN_ERROR;
}

AudioDevice::error_t
PortaudioAudioDevice::close ()
{
	PaError err = Pa_CloseStream(m_stream);
	if(err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Closed audio stream"));
		return AudioDevice::NO_ERROR;
	} else {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
			compose ("Unable to close stream: %s",
				Pa_GetErrorText (err)));
	}
	return AudioDevice::UNKNOWN_ERROR;
}

PaDeviceInfo const *
PortaudioAudioDevice::get_device_info () const
{
	return Pa_GetDeviceInfo(m_device_index);
}

channel_count_t
PortaudioAudioDevice::max_input_channels () const
{
	return get_device_info()->maxInputChannels;
}

channel_count_t
PortaudioAudioDevice::max_output_channels () const
{
	return get_device_info()->maxOutputChannels;
}

samplerate_t
PortaudioAudioDevice::get_default_samplerate () const
{
	return get_device_info()->defaultSampleRate;
}

void
PortaudioAudioDevice::get_supported_samplerates (
		std::vector<samplerate_t>& supported_rates) const
{
	std::vector<samplerate_t> possible_rates = {44100, 48000, 88200, 96000, 176400, 192000};
	PaStreamParameters input_params;
	PaStreamParameters output_params;

	input_params.device = m_device_index;
	input_params.channelCount = max_input_channels();
	input_params.sampleFormat = paFloat32;
	input_params.suggestedLatency = 0;
	input_params.hostApiSpecificStreamInfo = 0;

	output_params.device = m_device_index;
	output_params.channelCount = max_output_channels();
	output_params.sampleFormat = paFloat32;
	output_params.suggestedLatency = 0;
	output_params.hostApiSpecificStreamInfo = 0;

	for (auto const& rate : possible_rates) {
		if (paFormatIsSupported == Pa_IsFormatSupported(
					max_input_channels() > 0 ? &input_params : NULL,
					max_output_channels() > 0 ? &output_params : NULL,
					rate))
		{
			supported_rates.push_back (rate);
		}
	}
}

} // namespace mojo
