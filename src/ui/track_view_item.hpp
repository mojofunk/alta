
#ifndef GMOJO_TRACK_VIEW_ITEM_INCLUDED
#define GMOJO_TRACK_VIEW_ITEM_INCLUDED

namespace gmojo {

class TrackControl;
class TrackCanvasItem;

class TrackViewItem
{
public:

	virtual ~TrackViewItem ();

	virtual void set_height (double height) = 0;

	virtual TrackControl* get_track_control () = 0;

	virtual TrackCanvasItem* get_track_canvas_item () = 0;

};

} // namespace gmojo

#endif
