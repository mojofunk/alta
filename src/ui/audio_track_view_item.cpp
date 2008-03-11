
#include <ui/audio_track_view_item.hpp>

#include <ui/audio_track_control.hpp>

namespace gmojo {

AudioTrackViewItem::AudioTrackViewItem (AudioTrack* at)
	:
		m_audio_track(at)
		, m_control(new AudioTrackControl(at))
{

}

void
AudioTrackViewItem::set_height (double height)
{

}

TrackControl*
AudioTrackViewItem::get_track_control ()
{
	return m_control;
}

TrackCanvasItem*
AudioTrackViewItem::get_track_canvas_item ()
{
	return 0;
}


} // namespace gmojo
