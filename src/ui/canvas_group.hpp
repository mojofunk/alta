
#ifndef GMOJO_CANVAS_GROUP_INCLUDED
#define GMOJO_CANVAS_GROUP_INCLUDED

#include <ui/canvas_item.hpp>

namespace gmojo {

class CanvasGroup : public CanvasItem
{
public:
	CanvasGroup (CanvasItem* parent, TrackCanvas* track_canvas)
		:
			CanvasItem(goo_canvas_group_new (parent->get_canvas_item()) , track_canvas)
	{ }

	CanvasGroup (TrackCanvas* track_canvas)
		:
			CanvasItem(goo_canvas_group_new (NULL) , track_canvas)
	{ }
};

}

#endif
