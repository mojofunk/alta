
#ifndef GMOJO_AUDIO_TRACK_VIEW_ITEM
#define GMOJO_AUDIO_TRACK_VIEW_ITEM

#include <ui/track_view_item.hpp>

namespace gmojo {

class AudioTrack;
class TrackControl;
class TrackCanvasItem;

class AudioTrackViewItem : public TrackViewItem
{
public: // constructors

	AudioTrackViewItem (AudioTrack* at);

public: // TrackViewItem interface

	virtual void set_height (double height);

	virtual TrackControl* get_track_control ();

	virtual TrackCanvasItem* get_track_canvas_item ();

private: // member data

	AudioTrack* m_audio_track;

	TrackControl* m_control;

	TrackCanvasItem* m_canvas_item;

};

} // namespace gmojo

#endif
