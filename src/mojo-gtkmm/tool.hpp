
#ifndef UI_TOOL
#define UI_TOOL

#include <string>

#include <goocanvasmm/canvas.h>

namespace ui {

class Tool
{
public:

	virtual ~Tool () { }

public:

	virtual const std::string get_name() const = 0;

	virtual bool on_item_button_press_event (Glib::RefPtr<Goocanvas::Item>, GdkEventButton*) = 0;
	virtual bool on_item_button_release_event (Glib::RefPtr<Goocanvas::Item>, GdkEventButton*) = 0;
	virtual bool on_item_motion_notify_event (Glib::RefPtr<Goocanvas::Item>, GdkEventMotion*) = 0;
	virtual bool on_item_scroll_event (Glib::RefPtr<Goocanvas::Item>, GdkEventScroll*) = 0;
	virtual bool on_item_key_press_event (Glib::RefPtr<Goocanvas::Item>, GdkEventKey*) = 0;
	virtual bool on_item_key_release_event (Glib::RefPtr<Goocanvas::Item>, GdkEventKey*) = 0;
	virtual bool on_item_left_event (Glib::RefPtr<Goocanvas::Item>, GdkEventCrossing*) = 0;
	virtual bool on_item_entered_event (Glib::RefPtr<Goocanvas::Item>, GdkEventCrossing*) = 0;

	// register stock
};

} // namespace ui

#endif
