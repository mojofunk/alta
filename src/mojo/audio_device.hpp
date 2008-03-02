
#ifndef MOJO_AUDIO_DEVICE_INCLUDED
#define MOJO_AUDIO_DEVICE_INCLUDED

#include <mojo/types.hpp>

namespace mojo {

/**
 * An AudioDevice has a number of input or output channels
 *
 */
class AudioDevice
{
public: // ctors

	virtual ~AudioDevice ();

public: // interface

	typedef int callback_t(count_t frames);

	enum error_t {
		NO_ERROR = 0
	};

	enum callback_result_t {
		CONTINUE = 0,
		ABORT
	};

	/// @return The name of the device. unique??
	virtual std::string get_name () const = 0;

	// input_latency/output_latency??
	// user_data
	virtual error_t open (callback_t* cb,
			samplerate_t samplerate);

	// wait till callback completed?
	virtual error_t close ();

	//virtual channel_count_t get_sink_count () const = 0;

	//virtual channel_count_t get_source_count () const = 0;

	//virtual get_current_buffer_size () const;
	//virtual get_min_buffer_size () const;
	//virtual get_max_buffer_size () const;

	//virtual get_current_samplerate () const;
	
	//virtual get_min_samplerate () const;
	//virtual get_max_samplerate () const;
	
	//virtual double get_input_latency () = 0;
	//virtual double get_output_latency () = 0;

};

} // namespace mojo

#endif