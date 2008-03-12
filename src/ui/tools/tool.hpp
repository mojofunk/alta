
#ifndef GMOJO_TOOL_INCLUDED
#define GMOJO_TOOL_INCLUDED

#include <string>

#include <gtk/gtk.h>

namespace gmojo {

class TrackCanvas;
class CanvasItem;

/**
 * A Tool should only depend on internal class interfaces
 *
 * Tools should not depend on a canvas implementation, that
 * should be hidden by the TrackCanvas and CanvasItems
 *
 * Tools should not depend on Gtk+ interfaces/classes like
 * event types, keyboard modifiers etc.
 *
 */
class Tool
{
public:

	virtual ~Tool () { }

public:

	virtual const std::string get_name() const = 0;

	virtual void on_button_press (TrackCanvas*, CanvasItem*, GdkEventButton*) = 0;
	
	virtual void on_button_release (TrackCanvas*, CanvasItem*, GdkEventButton*) = 0;

	//virtual void on_motion () = 0;

	//virtual bool on_key_press () = 0;

	//virtual bool on_key_release () = 0;

	// register stock 
};

} // namespace gmojo

#endif
