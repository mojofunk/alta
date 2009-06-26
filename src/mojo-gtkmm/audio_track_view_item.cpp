
#include "audio_track_view_item.hpp"

namespace ui {

AudioTrackViewItem::AudioTrackViewItem (mojo::Track* at)
	: m_audio_track(at)
	, m_audio_track_list_item(new AudioTrackListItem(at))
	, m_audio_track_canvas_item(new AudioTrackCanvasItem(at))
{

}

void
AudioTrackViewItem::set_height (double height)
{


}

TrackListItem*
AudioTrackViewItem::get_track_list_item ()
{
	return m_audio_track_list_item.get();

}

TrackCanvasItem*
AudioTrackViewItem::get_track_canvas_item ()
{
	return m_audio_track_canvas_item.get();
}

} // namespace ui
