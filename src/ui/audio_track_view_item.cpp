
#include <ui/audio_track_view_item.hpp>

namespace gmojo {

AudioTrackViewItem::AudioTrackViewItem (AudioTrack* at)
	:
		m_audio_track(at)
{

}

void
AudioTrackViewItem::set_height (double height)
{

}

TrackControl*
AudioTrackViewItem::get_track_control ()
{
	return 0;
}

TrackCanvasItem*
AudioTrackViewItem::get_track_canvas_item ()
{
	return 0;
}


} // namespace gmojo
