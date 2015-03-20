#include "portaudio_audio_device.hpp"

namespace mojo {

PortaudioAudioDevice::PortaudioAudioDevice ()
{

}

PortaudioAudioDevice::~PortaudioAudioDevice ()
{


}

AudioDevice::error_t
PortaudioAudioDevice::open (uint32_t input_channels,
	                        uint32_t output_channels,
	                        uint32_t samplerate,
	                        uint32_t buffersize,
	                        callback_t* cb)
{



}

AudioDevice::error_t
PortaudioAudioDevice::close ()
{


}

} // namespace mojo
