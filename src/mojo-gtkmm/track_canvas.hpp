
#ifndef UI_TRACK_CANVAS
#define UI_TRACK_CANVAS

#include <gtkmm/scrolledwindow.h>

#include <goocanvasmm/canvas.h>

namespace ui {

class TrackCanvas : public Gtk::ScrolledWindow
{
public:

	TrackCanvas ();

private:

	Goocanvas::Canvas m_canvas;

};

} // namespace ui

#endif
