
#ifndef MOJO_AUDIO_CLIP_PTR_INCLUDED
#define MOJO_AUDIO_CLIP_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioClip;

	typedef boost::shared_ptr<AudioClip>    AudioClipSPtr;
	typedef boost::weak_ptr<AudioClip>      AudioClipWPtr;

} // namespace mojo

#endif
