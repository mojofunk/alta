#ifndef MOJO_AUDIO_TRACK
#define MOJO_AUDIO_TRACK

#include <mojo/track.hpp>
#include <mojo/typedefs.hpp>

namespace mojo {

/**
 * An AudioTrack can contain:
 *
 * A sequence of audio events
 * A number of input and output Busses(with varying formats)
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

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public:

	AudioSequenceSPtr get_audio_sequence ();

private:

	AudioSequenceSPtr m_audio_sequence;

private:

	static const char* const s_property_audio_sequence;
	
};

} // namespace mojo

#endif
