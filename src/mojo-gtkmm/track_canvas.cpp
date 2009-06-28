
#include "track_canvas.hpp"

#include "log.hpp"

namespace ui {

TrackCanvas::TrackCanvas ()
{
	LOG;
	Glib::RefPtr<Goocanvas::Item> ri = get_root_item();

	connect_item_signals(get_root_item());

}

void
TrackCanvas::connect_item_signals (Glib::RefPtr<Goocanvas::Item> item)
{
	item->signal_button_press_event().connect (sigc::mem_fun (this, &TrackCanvas::on_button_press));
	item->signal_button_release_event().connect (sigc::mem_fun (this, &TrackCanvas::on_button_release));
	item->signal_motion_notify_event().connect (sigc::mem_fun (this, &TrackCanvas::on_motion));
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

bool
TrackCanvas::on_button_press (Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* ev)
{
	LOG;
	m_tools.on_button_press (this, item, ev);
	return true;
}

bool
TrackCanvas::on_button_release (Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* ev)
{
	LOG;
	m_tools.on_button_release (this, item, ev);
	return true;
}

bool
TrackCanvas::on_motion (Glib::RefPtr<Goocanvas::Item> item, GdkEventMotion* ev)
{
	LOG;
	m_tools.on_motion (this, item, ev);
	return true;
}

} // namespace ui
