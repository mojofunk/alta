
#ifndef MOJO_AUDIO_DEVICE_INCLUDED
#define MOJO_AUDIO_DEVICE_INCLUDED

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

	/// @return The name of the device. unique??
	virtual std::string get_name () const = 0;

	//virtual channel_count_t get_sink_count () const = 0;

	//virtual channel_count_t get_source_count () const = 0;

	//virtual get_current_buffer_size () const;
	//virtual get_min_buffer_size () const;
	//virtual get_max_buffer_size () const;

	//virtual get_current_samplerate () const;
	//virtual get_min_samplerate () const;
	//virtual get_max_samplerate () const;


};

} // namespace mojo

#endif
