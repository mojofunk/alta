#ifndef MOJO_AUDIO_DEVICE_H
#define MOJO_AUDIO_DEVICE_H

#include "mojo-audio-driver.hpp"

namespace mojo {

/**
 * An AudioDevice has a number of input or output streams
 *
 * Each stream can be either an input stream(source) or a output stream(sink)
 *
 * Each stream can have a number of channels
 *
 * Each stream can have a channel map
 *
 * Each stream has a number of ports
 *
 * Each Port has a buffer
 *
 */
class AudioDevice
{
public: // ctors

	virtual ~AudioDevice ();

public: // interface

	typedef int callback_t(const float* input_buffer,
	                       const float* output_buffer,
	                       count_t frames,
	                       void* user_data);

	enum error_t {
		NO_ERROR = 0,
		UNKNOWN_ERROR = -1000
	};

	enum callback_result_t {
		CONTINUE = 0,
		ABORT
	};

	/// @return The name of the device. unique??
	virtual std::string get_name () const = 0;

	virtual error_t open (uint32_t input_channels,
	                      uint32_t output_channels,
	                      uint32_t samplerate,
	                      uint32_t buffersize,
	                      callback_t* cb) = 0;

	virtual error_t start () = 0;

	virtual error_t stop () = 0;

	virtual error_t close () = 0;

	virtual channel_count_t max_input_channels () const = 0;

	virtual channel_count_t max_output_channels () const = 0;

	virtual samplerate_t get_default_samplerate () const = 0;

	virtual void get_supported_samplerates (std::vector<samplerate_t>&) const = 0;

	//virtual double get_input_latency () = 0;

	//virtual double get_output_latency () = 0;

	//virtual get_current_buffer_size () const;
	//virtual get_min_buffer_size () const;
	//virtual get_max_buffer_size () const;

	//virtual get_current_samplerate () const;
	
	//virtual get_min_samplerate () const;
	//virtual get_max_samplerate () const;
	

};

} // namespace mojo

#endif // MOJO_AUDIO_DEVICE_H
