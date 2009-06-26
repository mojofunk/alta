
#ifndef UI_TRACK_CANVAS_ITEM
#define UI_TRACK_CANVAS_ITEM

#include <inttypes.h>

#include <goocanvasmm/group.h>

namespace ui {

class TrackCanvasItem : public Goocanvas::Group
{
protected:

	TrackCanvasItem ();
	virtual ~TrackCanvasItem ();

public:

	virtual void set_height () = 0;

	virtual uint32_t get_height () const = 0;

	virtual void set_selected (bool) = 0;

	virtual bool get_selected () const = 0;

};

} // namespace ui

#endif
