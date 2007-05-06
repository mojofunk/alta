
#ifndef MOJO_PATHS_INCLUDED
#define MOJO_PATHS_INCLUDED

#include <libido/audio_track.hpp>
#include <libido/event.hpp>

namespace mojo {

/**
 * An AudioTrack can contain:
 *
 * A timeline of audio events
 * A number of channels
 * A format type mono/stereo/etc
 * A Panner?
 *
 * An AudioTrack doesn't contain:
 *
 * The state of the connections to and from 
 * the track.
 */
class AudioTrack : public ido::IAudioTrack
{
public:

	AudioTrack();

	// inherited from ido::Object
	virtual const ido::id_t get_identifier() const;

	virtual void set_identifier(const ido::id_t);
	
	// inherited from ido::AudioTrack
	virtual const std::string& get_name() const;

	virtual bool set_name(const std::string& name);

private:

	ido::id_t m_id;
	
	std::string m_name;

};

} // namespace mojo

#endif // MOJO_PATHS_INCLUDED
