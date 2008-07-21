
#ifndef GMOJO_TRACK_PTR
#define GMOJO_TRACK_PTR

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace gmojo {

	class Track;

	typedef boost::shared_ptr<Track>    TrackSPtr;
	typedef boost::weak_ptr<Track>      TrackWPtr;

} // namespace gmojo

#endif
