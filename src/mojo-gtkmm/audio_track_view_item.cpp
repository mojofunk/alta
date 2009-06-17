
#include "audio_track_view_item.hpp"

namespace ui {

AudioTrackViewItem::AudioTrackViewItem (mojo::Track* at)
	: m_audio_track(at)
{


}

void
AudioTrackViewItem::set_height (double height)
{


}

TrackListItem*
AudioTrackViewItem::get_track_list_item ()
{
	return 0;

}

TrackCanvasItem*
AudioTrackViewItem::get_track_canvas_item ()
{
	return 0;
}

} // namespace ui
