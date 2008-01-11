#ifndef MOJO_AUDIO_TRACK_INCLUDED
#define MOJO_AUDIO_TRACK_INCLUDED

#include <mojo/track.hpp>

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
class AudioTrack : public Track
{
public:

	// constructors
	AudioTrack ();

public:

	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual std::vector<std::string> get_property_names () const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

};

} // namespace mojo

#endif
