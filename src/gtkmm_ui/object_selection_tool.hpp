
#ifndef UI_OBJECT_SELECTION_TOOL
#define UI_OBJECT_SELECTION_TOOL

namespace ui {

class ObjectSelectionTool : public Tool {
public:
	ObjectSelectionTool();

public: // Tool interface
	const std::string get_name() const;

	bool on_item_button_press_event(Glib::RefPtr<Goocanvas::Item>,
	                                GdkEventButton*);
	bool on_item_button_release_event(Glib::RefPtr<Goocanvas::Item>,
	                                  GdkEventButton*);
	bool on_item_motion_notify_event(Glib::RefPtr<Goocanvas::Item>,
	                                 GdkEventMotion*);
	bool on_item_scroll_event(Glib::RefPtr<Goocanvas::Item>, GdkEventScroll*);
	bool on_item_key_press_event(Glib::RefPtr<Goocanvas::Item>, GdkEventKey*);
	bool on_item_key_release_event(Glib::RefPtr<Goocanvas::Item>, GdkEventKey*);
	bool on_item_left_event(Glib::RefPtr<Goocanvas::Item>, GdkEventCrossing*);
	bool on_item_entered_event(Glib::RefPtr<Goocanvas::Item>, GdkEventCrossing*);
};

} // namespace ui

#endif
