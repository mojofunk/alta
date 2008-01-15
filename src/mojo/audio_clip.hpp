
#ifndef MOJO_AUDIO_CLIP_INCLUDED
#define MOJO_AUDIO_CLIP_INCLUDED

#include <mojo/types.hpp>
#include <mojo/object.hpp>

namespace mojo {

/**
 * A new AudioClip only references one audio file
 *
 * To support non-destructive editing of the audio file,
 * any processing of the original file results in a new
 * file being created.
 */
class AudioClip : public Object
{
public:

	AudioClip ();

	//AudioClip ();

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

};

} // namespace mojo

#endif
