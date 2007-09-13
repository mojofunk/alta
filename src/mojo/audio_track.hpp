#ifndef MOJO_AUDIO_TRACK_INCLUDED
#define MOJO_AUDIO_TRACK_INCLUDED

//#include <boost/signal.hpp>

#include <mojo/object.hpp>

namespace mojo {

/**
 * An AudioTrack can contain:
 *
 * A sequence of audio events
 * A number of channels
 * A format type mono/stereo/etc
 * A Panner?
 *
 * An AudioTrack doesn't contain:
 *
 * - the state of the connections to and from the track.
 * - reference to any buffers, they are passed in for processing
 */
class AudioTrack : public Object
{
public:

	// typedefs
	typedef boost::signal<void ()>       name_change_signal_t;

public:

	// constructors
	AudioTrack ();

public:

	std::string get_name () const;

public:

	void set_name (const std::string& name);

	name_change_signal_t& signal_name_change ();
	//{ return m_signal_name_change; }

private:
	
	// friend class Session
	//
	// process (transport_info, buffers) const
	
private:

	// member data
	std::string m_name;

	/**
	 * references a BufferedAudioStream?
	 */
	// audio_stream_ptr

private:

	// signal members
	name_change_signal_t         m_signal_name_change;

};

} // namespace mojo

#endif // MOJO_AUDIO_TRACK_INCLUDED
