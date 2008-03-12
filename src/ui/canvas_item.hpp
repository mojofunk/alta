
#ifndef GMOJO_CANVAS_ITEM_INCLUDED
#define GMOJO_CANVAS_ITEM_INCLUDED

#include <goocanvas.h>

namespace gmojo {

class TrackCanvas;

class CanvasItem {
public:

	virtual ~CanvasItem ();

protected:

	CanvasItem (GooCanvasItem*, TrackCanvas*);

public:

	virtual GooCanvasItem* get_canvas_item ()
	{ return m_item; }

public: // static event handlers

	static gboolean button_press_event_handler (GooCanvasItem*,
			GooCanvasItem*, GdkEventButton*, gpointer);

	static gboolean button_release_event_handler (GooCanvasItem*,
			GooCanvasItem*, GdkEventButton*, gpointer);

	static gboolean motion_notify_event_handler (GooCanvasItem*,
			GooCanvasItem*, GdkEventMotion*, gpointer);

public: // virtual event handlers

	virtual bool on_button_press_event (GdkEventButton*);

	virtual bool on_button_release_event (GdkEventButton*);

	virtual bool on_motion_notify_event (GdkEventMotion*);

private: // member data

	GooCanvasItem* m_item;

	TrackCanvas* m_track_canvas;

};

} // namespace gmojo

#endif
