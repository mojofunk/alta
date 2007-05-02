
#ifndef GMOJO_TRACK_CONTROL_INCLUDED
#define GMOJO_TRACK_CONTROL_INCLUDED

#include <boost/noncopyable.hpp>

#include <gtk/gtk.h>

namespace gmojo {

class TrackControl : boost::noncopyable
{
public:

	virtual ~TrackControl();

	/**
	 * The widget that gets packed into the TrackControlList
	 */
	virtual GtkWidget* widget() = 0;

};

} // namespace gmojo

#endif // GMOJO_TRACK_CONTROL_INCLUDED
