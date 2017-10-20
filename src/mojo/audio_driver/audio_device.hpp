#ifndef MOJO_AUDIO_DEVICE_H
#define MOJO_AUDIO_DEVICE_H

/**
 *
 */
class AudioDevice
{
public: // ctors
	virtual ~AudioDevice();

public: // interface
	enum callback_result_t { CONTINUE = 0, ABORT };

	enum error_t { NO_ERROR = 0, UNKNOWN_ERROR = -1000 };

	using callback_t = callback_result_t(const float* input_buffer,
	                                     const float* output_buffer,
	                                     count_t frames,
	                                     void* user_data);

	/// @return The name of the device. unique??
	virtual std::string get_name() const = 0;

	virtual error_t open(uint32_t input_channels,
	                     uint32_t output_channels,
	                     uint32_t samplerate,
	                     uint32_t buffersize,
	                     callback_t* cb,
	                     void* user_data) = 0;

	virtual bool is_open() = 0;

	virtual error_t start() = 0;

	virtual bool is_active() = 0;

	virtual error_t stop() = 0;

	virtual bool is_stopped() = 0;

	virtual error_t abort() = 0;

	virtual error_t close() = 0;

	virtual std::string get_error_string(error_t) = 0;

	virtual channel_count_t max_input_channels() const = 0;

	virtual channel_count_t max_output_channels() const = 0;

	virtual samplerate_t get_default_samplerate() const = 0;

	virtual void get_supported_samplerates(std::vector<samplerate_t>&) const = 0;

	// virtual uint32_t get_default_buffersize() const = 0;

	// virtual void get_supported_buffer_sizes(std::vector<uint32_t>&) const = 0;

	virtual double get_input_latency() = 0;

	virtual double get_output_latency() = 0;

	virtual uint32_t get_current_samplerate() const = 0;

	virtual double get_cpu_load() const = 0;

	// virtual get_min_buffer_size () const;
	// virtual get_max_buffer_size () const;
};

#endif // MOJO_AUDIO_DEVICE_H
