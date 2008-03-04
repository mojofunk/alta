
#ifndef GMOJO_TRACK_INCLUDED
#define GMOJO_TRACK_INCLUDED

#include <ui/gtk/widget.hpp>

namespace gmojo {

/**
 * Track is an interface that all Track types derive from. 
 * This is so the TrackView doesn't need to know about specific 
 * track types.
 */
class Track
{
public:

	virtual ~Track() { }

	/**
	 * TrackControl an widget that gets packed into the 
	 * TrackControlList widget, different track types create 
	 * custom TrackControl derived widgets.
	 */
	virtual gtk::Widget* track_control() = 0;

};

} // namespace gmojo

#endif // GMOJO_TRACK_INCLUDED
