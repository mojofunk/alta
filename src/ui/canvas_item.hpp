
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

public:

	static gboolean button_press_event_handler (GooCanvasItem*,
			GooCanvasItem*, GdkEventButton*, gpointer);

public:

	bool on_button_press_event (GdkEventButton*);

private:

	GooCanvasItem* m_item;

	TrackCanvas* m_track_canvas;

};

} // namespace gmojo

#endif
