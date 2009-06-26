
#ifndef UI_TRACK_VIEW_ITEM
#define UI_TRACK_VIEW_ITEM

#include "track_canvas_item.hpp"

namespace ui {

class TrackListItem;

class TrackViewItem
{
public:

	virtual ~TrackViewItem ();

	virtual void set_height (double height) = 0;

	virtual TrackListItem* get_track_list_item () = 0;

	virtual Glib::RefPtr<TrackCanvasItem> get_track_canvas_item () = 0;

};

} // namespace ui

#endif
