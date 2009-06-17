
#ifndef UI_AUDIO_TRACK_VIEW_ITEM
#define UI_AUDIO_TRACK_VIEW_ITEM

#include <mojo/mojo.hpp>

#include "track_view_item.hpp"

namespace ui {

class AudioTrackViewItem : public TrackViewItem
{
public:

	AudioTrackViewItem (mojo::Track* at);

	virtual void set_height (double height);

	virtual TrackListItem* get_track_list_item ();

	virtual TrackCanvasItem* get_track_canvas_item ();

private:

	mojo::Track* m_audio_track;

};

} // namespace ui

#endif
