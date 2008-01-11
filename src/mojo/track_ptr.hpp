
#ifndef MOJO_TRACK_PTR_INCLUDED
#define MOJO_TRACK_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class Track;

	typedef boost::shared_ptr<Track>    TrackSPtr;
	typedef boost::weak_ptr<Track>      TrackWPtr;

} // namespace mojo

#endif
