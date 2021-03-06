MOJO_DEBUG_DOMAIN(PORTAUDIO_DEVICE)

PortaudioAudioDevice::PortaudioAudioDevice(PaDeviceIndex index)
    : m_device_index(index)
    , m_stream(0)
    , m_user_data(0)
{
}

PortaudioAudioDevice::~PortaudioAudioDevice()
{
}

std::string
PortaudioAudioDevice::get_name() const
{
	return get_device_info()->name;
}

int
PortaudioAudioDevice::portaudio_callback(
    const void* input_buffer,
    void* output_buffer,
    unsigned long frames_per_buffer,
    const PaStreamCallbackTimeInfo* time_info,
    PaStreamCallbackFlags status_flags,
    void* user_data)
{
	MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
	               compose("Portaudio Callback: frames %", frames_per_buffer));
	PortaudioAudioDevice* device = static_cast<PortaudioAudioDevice*>(user_data);

	callback_result_t result = device->m_callback((float*)input_buffer,
	                                              (float*)output_buffer,
	                                              frames_per_buffer,
	                                              device->m_user_data);

	if (result == CONTINUE) return 0;
	return 1;
}

AudioDevice::error_t
PortaudioAudioDevice::open(uint32_t input_channels,
                           uint32_t output_channels,
                           uint32_t samplerate,
                           uint32_t buffersize,
                           callback_t* cb,
                           void* user_data)
{
	PaStreamParameters input_params = get_default_input_params();
	PaStreamParameters output_params = get_default_output_params();

	input_params.channelCount = input_channels;
	output_params.channelCount = output_channels;

	m_callback = cb;
	m_user_data = user_data;

	PaError err = Pa_OpenStream(&m_stream,
	                            input_channels > 0 ? &input_params : NULL,
	                            output_channels > 0 ? &output_params : NULL,
	                            samplerate,
	                            buffersize,
	                            paDitherOff | paClipOff,
	                            portaudio_callback,
	                            this);

	if (err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE, "Opened audio stream");
		return AudioDevice::NO_ERROR;
	}
	MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
	               compose("Unable to open stream: %", Pa_GetErrorText(err)));
	return (AudioDevice::error_t)err;
}

bool
PortaudioAudioDevice::is_open()
{
	return m_stream != NULL;
}

AudioDevice::error_t
PortaudioAudioDevice::start()
{
	PaError err = Pa_StartStream(m_stream);
	if (err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE, "Started audio stream");
		return AudioDevice::NO_ERROR;
	}
	MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
	               compose("Unable to start stream: %", Pa_GetErrorText(err)));
	return AudioDevice::UNKNOWN_ERROR;
}

bool
PortaudioAudioDevice::is_active()
{
	if (m_stream == NULL) return false;

	PaError err = Pa_IsStreamActive(m_stream);

	if (err == 1) return true;
	if (err != 0) {
		compose("Error: %", Pa_GetErrorText(err));
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE, "Stopped audio stream");
	}
	return false;
}

AudioDevice::error_t
PortaudioAudioDevice::stop()
{
	PaError err = Pa_StopStream(m_stream);
	if (err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE, "Stopped audio stream");
		return AudioDevice::NO_ERROR;
	}
	MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
	               compose("Unable to stop stream: %", Pa_GetErrorText(err)));
	return AudioDevice::UNKNOWN_ERROR;
}

bool
PortaudioAudioDevice::is_stopped()
{
	if (m_stream == NULL) return false;

	PaError err = Pa_IsStreamStopped(m_stream);

	if (err == 1) return true;
	if (err != 0) {
		compose("Error: %", Pa_GetErrorText(err));
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE, "Stopped audio stream");
	}
	return false;
}

AudioDevice::error_t
PortaudioAudioDevice::close()
{
	PaError err = Pa_CloseStream(m_stream);
	if (err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE, "Closed audio stream");
		m_stream = NULL;
		return AudioDevice::NO_ERROR;
	}
	MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
	               compose("Unable to close stream: %", Pa_GetErrorText(err)));
	m_stream = NULL;
	return AudioDevice::UNKNOWN_ERROR;
}

AudioDevice::error_t
PortaudioAudioDevice::abort()
{
	PaError err = Pa_AbortStream(m_stream);
	if (err == paNoError) {
		MOJO_DEBUG_MSG(PORTAUDIO_DEVICE, "Aborted audio stream");
		m_stream = NULL;
		return AudioDevice::NO_ERROR;
	}
	MOJO_DEBUG_MSG(PORTAUDIO_DEVICE,
	               compose("Unable to abort stream: %", Pa_GetErrorText(err)));
	m_stream = NULL;
	return AudioDevice::UNKNOWN_ERROR;
}

std::string
PortaudioAudioDevice::get_error_string(error_t err)
{
	return Pa_GetErrorText(err);
}

PaDeviceInfo const*
PortaudioAudioDevice::get_device_info() const
{
	return Pa_GetDeviceInfo(m_device_index);
}

PaStreamParameters
PortaudioAudioDevice::get_default_input_params() const
{
	PaStreamParameters input_params;
	input_params.device = m_device_index;
	input_params.channelCount = max_input_channels();
	input_params.sampleFormat = paFloat32;
	input_params.suggestedLatency = 0;
	input_params.hostApiSpecificStreamInfo = 0;
	return input_params;
}

PaStreamParameters
PortaudioAudioDevice::get_default_output_params() const
{
	PaStreamParameters output_params;
	output_params.device = m_device_index;
	output_params.channelCount = max_output_channels();
	output_params.sampleFormat = paFloat32;
	output_params.suggestedLatency = 0;
	output_params.hostApiSpecificStreamInfo = 0;
	return output_params;
}

channel_count_t
PortaudioAudioDevice::max_input_channels() const
{
	return get_device_info()->maxInputChannels;
}

channel_count_t
PortaudioAudioDevice::max_output_channels() const
{
	return get_device_info()->maxOutputChannels;
}

samplerate_t
PortaudioAudioDevice::get_default_samplerate() const
{
	return get_device_info()->defaultSampleRate;
}

void
PortaudioAudioDevice::get_supported_samplerates(
    std::vector<samplerate_t>& supported_rates) const
{
	PaStreamParameters input_params = get_default_input_params();
	PaStreamParameters output_params = get_default_output_params();

	for (auto const& rate : get_common_samplerates()) {
		if (paFormatIsSupported ==
		    Pa_IsFormatSupported(max_input_channels() > 0 ? &input_params : NULL,
		                         max_output_channels() > 0 ? &output_params : NULL,
		                         rate)) {
			supported_rates.push_back(rate);
		}
	}
}

double
PortaudioAudioDevice::get_input_latency()
{
	if (m_stream == NULL) return 0.0;

	const PaStreamInfo* info = Pa_GetStreamInfo(m_stream);

	if (info == NULL) return 0.0;

	return info->inputLatency;
}

double
PortaudioAudioDevice::get_output_latency()
{
	if (m_stream == NULL) return 0.0;

	const PaStreamInfo* info = Pa_GetStreamInfo(m_stream);

	if (info == NULL) return 0.0;

	return info->outputLatency;
}

uint32_t
PortaudioAudioDevice::get_current_samplerate() const
{
	if (m_stream == NULL) return 0.0;

	const PaStreamInfo* info = Pa_GetStreamInfo(m_stream);

	if (info == NULL) return 0.0;

	return info->sampleRate;
}

double
PortaudioAudioDevice::get_cpu_load() const
{
	if (m_stream == NULL) return 0.0;

	return Pa_GetStreamCpuLoad(m_stream);
}
