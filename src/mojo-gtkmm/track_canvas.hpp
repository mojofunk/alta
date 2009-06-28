
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

	bool on_button_press (Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);

	bool on_button_release (Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);

	bool on_motion (Glib::RefPtr<Goocanvas::Item>, GdkEventMotion*);

private:

	TrackCanvasToolkit m_tools;

};

} // namespace ui

#endif
