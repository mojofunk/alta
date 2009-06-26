
#ifndef UI_TRACK_CANVAS
#define UI_TRACK_CANVAS

#include <gtkmm/scrolledwindow.h>

#include <goocanvasmm/canvas.h>

#include "track_canvas_item.hpp"

namespace ui {

class TrackCanvas : public Gtk::ScrolledWindow
{
public:

	TrackCanvas ();

public:

	void add (TrackCanvasItem*);

	void remove (TrackCanvasItem*);

private:

	Goocanvas::Canvas m_canvas;

};

} // namespace ui

#endif
