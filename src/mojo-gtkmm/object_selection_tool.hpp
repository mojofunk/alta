
#ifndef UI_OBJECT_SELECTION_TOOL
#define UI_OBJECT_SELECTION_TOOL

#include "tool.hpp"

namespace ui {

class ObjectSelectionTool : public Tool
{
public:

	ObjectSelectionTool ();

public: // Tool interface

	const std::string get_name() const;

	virtual bool on_button_press (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);

	virtual bool on_button_release (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventButton*);

	virtual bool on_motion (Goocanvas::Canvas*, Glib::RefPtr<Goocanvas::Item>, GdkEventMotion*);

};

} // namespace ui

#endif
