
#include "audio_track_view_item.hpp"

namespace ui {

AudioTrackViewItem::AudioTrackViewItem (mojo::Track* at)
	: m_audio_track(at)
	, m_audio_track_list_item(new AudioTrackListItem(at))
	, m_audio_track_canvas_item(AudioTrackCanvasItem::create(at))
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

Glib::RefPtr<TrackCanvasItem>
AudioTrackViewItem::get_track_canvas_item ()
{
	return Glib::RefPtr<TrackCanvasItem>::cast_dynamic(m_audio_track_canvas_item);
}

} // namespace ui
