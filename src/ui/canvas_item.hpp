
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

	virtual GooCanvasItem* get_canvas_item () const
	{ return m_item; }

	TrackCanvas* get_track_canvas () const
	{ return m_track_canvas; }

public: // static event handlers

	static gboolean button_press_event_handler (GooCanvasItem*,
			GooCanvasItem*, GdkEventButton*, gpointer);

	static gboolean button_release_event_handler (GooCanvasItem*,
			GooCanvasItem*, GdkEventButton*, gpointer);

	static gboolean motion_notify_event_handler (GooCanvasItem*,
			GooCanvasItem*, GdkEventMotion*, gpointer);

private: // member data

	GooCanvasItem* m_item;

	TrackCanvas* m_track_canvas;

};

} // namespace gmojo

#endif
