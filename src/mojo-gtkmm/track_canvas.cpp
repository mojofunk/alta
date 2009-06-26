

#include "track_canvas.hpp"

#include "log.hpp"

namespace ui {

TrackCanvas::TrackCanvas ()
{
	LOG;
	Gtk::ScrolledWindow::add (m_canvas);
}

void
TrackCanvas::add (TrackCanvasItem* item)
{
	LOG;
	Glib::RefPtr<Goocanvas::Item> ri = m_canvas.get_root_item();

	ri->add_child (item->get_group ());
}

void
TrackCanvas::remove (TrackCanvasItem* item)
{

}

} // namespace ui
