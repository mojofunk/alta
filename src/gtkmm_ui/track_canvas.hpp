#ifndef UI_TRACK_CANVAS
#define UI_TRACK_CANVAS

namespace ui {

/**
 * The length of the root canvas item is determined by the length of the project
 *
 * The tracks should be the same length as the root canvas item
 *
 * The height of the canvas is determined by the total heights of all the
 *TrackViewItems
 *
 * The order of the tracks on the canvas is controlled via the TrackCanvas
 *class.
 *
 * Goocanvas::Item items don't emit any signals when there size changes so if
 *the height
 * of a track changes then all the tracks below it will have move etc.
 *
 */
class TrackCanvas : public Goocanvas::Canvas {
public: // typedefs
	typedef std::list<Glib::RefPtr<TrackCanvasItem>> tci_list_t;

public: // ctors
	TrackCanvas();

public:
	void add(Glib::RefPtr<TrackCanvasItem>);

	void remove(Glib::RefPtr<TrackCanvasItem>);

	void connect_item_signals(Glib::RefPtr<Goocanvas::Item>);

private:
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

private:
	void on_track_canvas_item_height_changed(Glib::RefPtr<TrackCanvasItem>);

	double get_y_position_for_new_track();

private:
	static const int s_min_width = 400;

	// this should probably be shared with TrackList as they are
	// always the same height
	static const int s_min_height = 300;

	TrackCanvasToolkit m_tools;

	tci_list_t m_track_canvas_items;
};

} // namespace ui

#endif
