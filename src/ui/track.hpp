
#ifndef GMOJO_TRACK_INCLUDED
#define GMOJO_TRACK_INCLUDED

#include <boost/noncopyable.hpp>

#include <ui/track_control.hpp>

namespace gmojo {

/**
 * Track is an interface that all Track types derive from. 
 * This is so the TrackView doesn't need to know about specific 
 * track types.
 */
class Track : boost::noncopyable
{
public:

	virtual ~Track();

	/**
	 * TrackControl an widget that gets packed into the 
	 * TrackControlList widget, different track types create 
	 * custom TrackControl derived widgets.
	 */
	virtual TrackControl* track_control() = 0;

};

} // namespace gmojo

#endif // GMOJO_TRACK_INCLUDED
