
#ifndef GMOJO_TRACK_VIEW_INCLUDED
#define GMOJO_TRACK_VIEW_INCLUDED

#include <boost/noncopyable.hpp>

#include <ui/track_control.hpp>

namespace gmojo {

/**
 * Is TrackView an appropriate name? there could be an argument 
 * for calling the widget that contains all the tracks
 * the TrackView.
 */

/**
 * TrackView is an interface that all Track types
 * derive from. This is so the EditCanvas doesn't need to know
 * about specific track types.
 */
class TrackView : boost::noncopyable
{
public:

	virtual ~TrackView();

	/**
	 * TrackControl an widget that gets packed into the 
	 * TrackControlList widget, different track types create 
	 * custom TrackControl derived widgets.
	 */
	virtual TrackControl* track_control() = 0;

};

} // namespace gmojo

#endif // GMOJO_TRACK_VIEW_INCLUDED
