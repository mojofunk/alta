
#include "track_canvas.hpp"
#include "tool.hpp"

#include "log.hpp"

namespace ui {

TrackCanvas::TrackCanvas ()
{
	Glib::RefPtr<Goocanvas::Item> ri = get_root_item();

	connect_item_signals(get_root_item());
}

void
TrackCanvas::connect_item_signals (Glib::RefPtr<Goocanvas::Item> item)
{
	item->signal_button_press_event().connect (sigc::mem_fun (this, &TrackCanvas::on_item_button_press_event));
	item->signal_button_release_event().connect (sigc::mem_fun (this, &TrackCanvas::on_item_button_release_event));
	item->signal_motion_notify_event().connect (sigc::mem_fun (this, &TrackCanvas::on_item_motion_notify_event));
	item->signal_scroll_event().connect (sigc::mem_fun (*this, &TrackCanvas::on_item_scroll_event));
	item->signal_key_press_event().connect (sigc::mem_fun (*this, &TrackCanvas::on_item_key_press_event));
	item->signal_key_release_event().connect (sigc::mem_fun (*this, &TrackCanvas::on_item_key_release_event));
	item->signal_leave_notify_event().connect (sigc::mem_fun(*this, &TrackCanvas::on_item_left_event));
	item->signal_enter_notify_event().connect (sigc::mem_fun(*this, &TrackCanvas::on_item_entered_event));
}

void
TrackCanvas::add (Glib::RefPtr<TrackCanvasItem> item)
{
	Glib::RefPtr<Goocanvas::Item> ri = get_root_item();

	ri->add_child (Glib::RefPtr<Goocanvas::Item>::cast_dynamic(item));
}

void
TrackCanvas::remove (Glib::RefPtr<TrackCanvasItem> item)
{

}

bool
TrackCanvas::on_item_button_press_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_button_press_event (item, event);
	return true;
}

bool
TrackCanvas::on_item_button_release_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventButton* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_button_release_event (item, event);
	return true;
}

bool
TrackCanvas::on_item_motion_notify_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventMotion* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_motion_notify_event (item, event);
	return true;
}

bool
TrackCanvas::on_item_scroll_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventScroll* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_scroll_event (item, event);
	return true;

}

bool
TrackCanvas::on_item_key_press_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventKey* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_key_press_event (item, event);
	return true;

}

bool
TrackCanvas::on_item_key_release_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventKey* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_key_release_event (item, event);
	return true;

}

bool
TrackCanvas::on_item_left_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventCrossing* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_left_event (item, event);
	return true;

}

bool
TrackCanvas::on_item_entered_event (Glib::RefPtr<Goocanvas::Item> item, GdkEventCrossing* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_entered_event (item, event);
	return true;
}

} // namespace ui
