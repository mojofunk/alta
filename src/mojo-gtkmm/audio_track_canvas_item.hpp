
#ifndef UI_AUDIO_TRACK_CANVAS_ITEM
#define UI_AUDIO_TRACK_CANVAS_ITEM

#include <goocanvasmm/rect.h>

#include <mojo/mojo.hpp>

#include "track_canvas_item.hpp"

namespace ui {

class AudioTrackCanvasItem : public TrackCanvasItem
{
protected:

	AudioTrackCanvasItem (mojo::Track*);

public:

	static Glib::RefPtr<AudioTrackCanvasItem> create (mojo::Track*);

public:

	virtual void set_height ();

	virtual uint32_t get_height () const;

	virtual void set_selected (bool);

	virtual bool get_selected () const;

private:

	mojo::Track* m_audio_track;

	Glib::RefPtr<Goocanvas::Rect> m_rect;

};

} // namespace ui

#endif
