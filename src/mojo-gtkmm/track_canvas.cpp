

#include "track_canvas.hpp"

#include "log.hpp"

namespace ui {

TrackCanvas::TrackCanvas ()
{
	LOG;
}

void
TrackCanvas::add (Glib::RefPtr<TrackCanvasItem> item)
{
	LOG;
	Glib::RefPtr<Goocanvas::Item> ri = get_root_item();

	ri->add_child (Glib::RefPtr<Goocanvas::Item>::cast_dynamic(item));
}

void
TrackCanvas::remove (Glib::RefPtr<TrackCanvasItem> item)
{

}

} // namespace ui
