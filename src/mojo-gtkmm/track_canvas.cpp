

#include "track_canvas.hpp"

#include "log.hpp"

namespace ui {

TrackCanvas::TrackCanvas ()
{
	LOG;
}

void
TrackCanvas::add (TrackCanvasItem* item)
{
	LOG;
	Glib::RefPtr<Goocanvas::Item> ri = get_root_item();

	ri->add_child (item->get_group ());
}

void
TrackCanvas::remove (TrackCanvasItem* item)
{

}

} // namespace ui
