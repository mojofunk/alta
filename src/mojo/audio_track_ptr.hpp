
#ifndef MOJO_AUDIO_TRACK_PTR_INCLUDED
#define MOJO_AUDIO_TRACK_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioTrack;

	typedef boost::shared_ptr<AudioTrack>    AudioTrackSPtr;
	typedef boost::weak_ptr<AudioTrack>      AudioTrackWPtr;

} // namespace mojo

#endif
