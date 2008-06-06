
#ifndef UI_TRACK_VIEW_ITEM
#define UI_TRACK_VIEW_ITEM

namespace ui {

//class TrackControl;
//class TrackCanvasItem;

class TrackViewItem
{
public:

	virtual ~TrackViewItem ();

	virtual void set_height (double height) = 0;

	//virtual TrackControl* get_track_control () = 0;

	//virtual TrackCanvasItem* get_track_canvas_item () = 0;

};

} // namespace ui

#endif
