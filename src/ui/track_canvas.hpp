
#ifndef GMOJO_TRACK_CANVAS_INCLUDED
#define GMOJO_TRACK_CANVAS_INCLUDED

#include <ui/gtk/widget.hpp>
#include <ui/gtk/widget_ptr.hpp>

#include <ui/canvas_item.hpp>

namespace gmojo {

class Tool;

/**
 * TrackCanvas should only depend on the Tool Interface.
 *
 * Does the TrackCanvas need to handle any events itself? 
 *
 */
class TrackCanvas : public gtk::Widget
{
public:

	TrackCanvas ();

	~TrackCanvas ();

public: // gtk::Widget interface

	GtkWidget* get_widget () const
	{ return m_canvas; }

public:

	bool on_button_press_event (CanvasItem*, GdkEventButton*);

	bool on_button_release_event (CanvasItem*, GdkEventButton*);

	bool on_motion_notify_event (CanvasItem*, GdkEventMotion*);

private:

	GtkWidget* m_canvas;

	CanvasItem* m_root_item;

	Tool* m_tool;

	// list of TrackCanvasItems


};

}

#endif
