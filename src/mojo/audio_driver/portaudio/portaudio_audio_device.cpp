#include "portaudio_audio_device.hpp"

MOJO_DEBUG_DOMAIN(PORTAUDIO_DEVICE)

namespace mojo {

PortaudioAudioDevice::PortaudioAudioDevice (PaDeviceInfo const * info)
	: m_device_info(info)
{

}

PortaudioAudioDevice::~PortaudioAudioDevice ()
{


}

std::string
PortaudioAudioDevice::get_name () const
{
	return m_device_info->name;
}

AudioDevice::error_t
PortaudioAudioDevice::open (uint32_t input_channels,
	                        uint32_t output_channels,
	                        uint32_t samplerate,
	                        uint32_t buffersize,
	                        callback_t* cb)
{


	return AudioDevice::NO_ERROR;
}

AudioDevice::error_t
PortaudioAudioDevice::close ()
{


	return AudioDevice::NO_ERROR;
}

channel_count_t
PortaudioAudioDevice::get_input_count () const
{
	return m_device_info->maxInputChannels;
}

channel_count_t
PortaudioAudioDevice::get_output_count () const
{
	return m_device_info->maxOutputChannels;
}

samplerate_t
PortaudioAudioDevice::get_default_samplerate () const
{
	return m_device_info->defaultSampleRate;
}

} // namespace mojo
