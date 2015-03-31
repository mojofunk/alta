
#include "track_canvas.hpp"
#include "tool.hpp"

#include "log.hpp"

namespace ui {

TrackCanvas::TrackCanvas()
{
	Glib::RefPtr<Goocanvas::Item> ri = get_root_item();

	set_size_request(s_min_width, s_min_height);

	connect_item_signals(get_root_item());
}

void TrackCanvas::connect_item_signals(Glib::RefPtr<Goocanvas::Item> item)
{
	item->signal_button_press_event().connect(
	    sigc::mem_fun(this, &TrackCanvas::on_item_button_press_event));
	item->signal_button_release_event().connect(
	    sigc::mem_fun(this, &TrackCanvas::on_item_button_release_event));
	item->signal_motion_notify_event().connect(
	    sigc::mem_fun(this, &TrackCanvas::on_item_motion_notify_event));
	item->signal_scroll_event().connect(
	    sigc::mem_fun(*this, &TrackCanvas::on_item_scroll_event));
	item->signal_key_press_event().connect(
	    sigc::mem_fun(*this, &TrackCanvas::on_item_key_press_event));
	item->signal_key_release_event().connect(
	    sigc::mem_fun(*this, &TrackCanvas::on_item_key_release_event));
	item->signal_leave_notify_event().connect(
	    sigc::mem_fun(*this, &TrackCanvas::on_item_left_event));
	item->signal_enter_notify_event().connect(
	    sigc::mem_fun(*this, &TrackCanvas::on_item_entered_event));
}

void TrackCanvas::add(Glib::RefPtr<TrackCanvasItem> item)
{
	Glib::RefPtr<Goocanvas::Item> ri = get_root_item();

	ri->add_child(Glib::RefPtr<Goocanvas::Item>::cast_dynamic(item));

	item->set_height(40);  // default height
	item->set_width(2000); // project_length

	item->property_x() = 0;
	item->property_y() = get_y_position_for_new_track();

	m_track_canvas_items.push_back(item);

	// we need to store connection and remove it explicitly as
	// it holds a strong reference to the TrackViewItem
	item->signal_height_changed().connect(sigc::bind(
	    sigc::mem_fun(this, &TrackCanvas::on_track_canvas_item_height_changed),
	    item));
}

double TrackCanvas::get_y_position_for_new_track()
{
	double new_y_pos = 0;

	for (tci_list_t::const_iterator i = m_track_canvas_items.begin();
	     i != m_track_canvas_items.end();
	     ++i) {
		new_y_pos += (*i)->get_height();
	}
	return new_y_pos;
}

void TrackCanvas::remove(Glib::RefPtr<TrackCanvasItem> item)
{
}

void TrackCanvas::on_track_canvas_item_height_changed(
    Glib::RefPtr<TrackCanvasItem> ptr)
{
	LOG;
	// find the TCI in the display list and set the y positions
	// for each TCI after the one that changed in the list
}

bool TrackCanvas::on_item_button_press_event(Glib::RefPtr<Goocanvas::Item> item,
                                             GdkEventButton* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_button_press_event(item, event);
	return true;
}

bool
TrackCanvas::on_item_button_release_event(Glib::RefPtr<Goocanvas::Item> item,
                                          GdkEventButton* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_button_release_event(item, event);
	return true;
}

bool
TrackCanvas::on_item_motion_notify_event(Glib::RefPtr<Goocanvas::Item> item,
                                         GdkEventMotion* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_motion_notify_event(item, event);
	return true;
}

bool TrackCanvas::on_item_scroll_event(Glib::RefPtr<Goocanvas::Item> item,
                                       GdkEventScroll* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_scroll_event(item, event);
	return true;
}

bool TrackCanvas::on_item_key_press_event(Glib::RefPtr<Goocanvas::Item> item,
                                          GdkEventKey* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_key_press_event(item, event);
	return true;
}

bool TrackCanvas::on_item_key_release_event(Glib::RefPtr<Goocanvas::Item> item,
                                            GdkEventKey* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_key_release_event(item, event);
	return true;
}

bool TrackCanvas::on_item_left_event(Glib::RefPtr<Goocanvas::Item> item,
                                     GdkEventCrossing* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_left_event(item, event);
	return true;
}

bool TrackCanvas::on_item_entered_event(Glib::RefPtr<Goocanvas::Item> item,
                                        GdkEventCrossing* event)
{
	LOG;
	m_tools.get_current_tool()->on_item_entered_event(item, event);
	return true;
}

} // namespace ui
