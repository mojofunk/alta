
#ifndef MOJO_AUDIO_EVENT_PTR_INCLUDED
#define MOJO_AUDIO_EVENT_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioEvent;

	typedef boost::shared_ptr<AudioEvent>    AudioEventSPtr;
	typedef boost::weak_ptr<AudioEvent>      AudioEventWPtr;

} // namespace mojo

#endif
