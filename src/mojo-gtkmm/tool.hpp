
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

	virtual bool on_button_press (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventButton*) = 0;

	virtual bool on_button_release (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventButton*) = 0;

	virtual bool on_motion (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventMotion*) = 0;

	//virtual bool on_key_press () = 0;

	//virtual bool on_key_release () = 0;

	// register stock
};

} // namespace ui

#endif
