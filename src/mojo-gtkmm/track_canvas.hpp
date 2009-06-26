
#ifndef UI_TRACK_CANVAS
#define UI_TRACK_CANVAS

#include <goocanvasmm/canvas.h>

#include "track_canvas_item.hpp"

namespace ui {

class TrackCanvas : public Goocanvas::Canvas
{
public:

	TrackCanvas ();

public:

	void add (Glib::RefPtr<TrackCanvasItem>);

	void remove (Glib::RefPtr<TrackCanvasItem>);

};

} // namespace ui

#endif
