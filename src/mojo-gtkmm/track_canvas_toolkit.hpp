
#ifndef UI_TRACK_CANVAS_TOOLKIT
#define UI_TRACK_CANVAS_TOOLKIT

#include <goocanvasmm/canvas.h>

#include "toolkit.hpp"

namespace ui {

class TrackCanvas;

class TrackCanvasToolkit : public Toolkit
{
public:

	TrackCanvasToolkit ();

public: // signal handlers

	bool on_button_press (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);

	bool on_button_release (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);

	bool on_motion (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventMotion*);


};

} // namespace ui

#endif
