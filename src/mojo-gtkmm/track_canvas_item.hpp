
#ifndef UI_TRACK_CANVAS_ITEM
#define UI_TRACK_CANVAS_ITEM

#include <inttypes.h>

#include <goocanvasmm/group.h>

namespace ui {

class TrackCanvasItem : public Goocanvas::Group
{
public:

	typedef sigc::signal<void> height_changed_signal_t;

protected:

	TrackCanvasItem ();
	virtual ~TrackCanvasItem ();

public:

	virtual void set_height (int height) = 0;

	virtual uint32_t get_height () const = 0;

	virtual void set_width (int width) = 0;

	virtual uint32_t get_width () const = 0;

	virtual void set_selected (bool) = 0;

	virtual bool get_selected () const = 0;

public: // signal_accessors

	height_changed_signal_t& signal_height_changed ()
	{ return m_signal_height_changed; }

protected:

	height_changed_signal_t m_signal_height_changed;

};

} // namespace ui

#endif
