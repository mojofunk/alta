
#ifndef UI_TRACK_CANVAS
#define UI_TRACK_CANVAS

#include <goocanvasmm/canvas.h>

#include "track_canvas_item.hpp"
#include "track_canvas_toolkit.hpp"

namespace ui {

class TrackCanvas : public Goocanvas::Canvas
{
public:

	TrackCanvas ();

public:

	void add (Glib::RefPtr<TrackCanvasItem>);

	void remove (Glib::RefPtr<TrackCanvasItem>);

	void connect_item_signals (Glib::RefPtr<Goocanvas::Item>);

private:

	bool on_item_button_press_event (Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);
	bool on_item_button_release_event (Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);
	bool on_item_motion_notify_event (Glib::RefPtr<Goocanvas::Item>, GdkEventMotion*);
	bool on_item_scroll_event (Glib::RefPtr<Goocanvas::Item>, GdkEventScroll*);
	bool on_item_key_press_event (Glib::RefPtr<Goocanvas::Item>, GdkEventKey*);
	bool on_item_key_release_event (Glib::RefPtr<Goocanvas::Item>, GdkEventKey*);
	bool on_item_left_event (Glib::RefPtr<Goocanvas::Item>, GdkEventCrossing*);
	bool on_item_entered_event (Glib::RefPtr<Goocanvas::Item>, GdkEventCrossing*);

private:

	TrackCanvasToolkit m_tools;

};

} // namespace ui

#endif
