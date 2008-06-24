
#ifndef UI_AUDIO_TRACK_VIEW_ITEM
#define UI_AUDIO_TRACK_VIEW_ITEM

#include "track_view_item.hpp"

namespace ui {

class AudioTrack;

class AudioTrackViewItem : public TrackViewItem
{
public:

	AudioTrackViewItem (AudioTrack* at);

	virtual void set_height (double height);

	virtual TrackListItem* get_track_list_item ();

	virtual TrackCanvasItem* get_track_canvas_item ();

private:

	AudioTrack* m_audio_track;

};

} // namespace ui

#endif
