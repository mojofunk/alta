#ifndef MOJO_AUDIO_TRACK_INCLUDED
#define MOJO_AUDIO_TRACK_INCLUDED

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

	// constructors
	AudioTrack ();

public:

	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

public:

	std::string get_name () const;

public:

	void set_name (const std::string& name);

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

};

} // namespace mojo

#endif // MOJO_AUDIO_TRACK_INCLUDED
