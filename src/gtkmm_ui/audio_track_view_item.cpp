
#include "audio_track_view_item.hpp"

namespace ui {

AudioTrackViewItem::AudioTrackViewItem(mojo::Track* at)
    : m_audio_track(at)
    , m_audio_track_list_item(new AudioTrackListItem(at))
    , m_audio_track_canvas_item(AudioTrackCanvasItem::create(at))
{

	// get height for track saved in file if any otherwise set using default

	// need to connect to TrackListItem and TrackCanvasItem signals
	// for when height changes to keep both in sync
	m_audio_track_canvas_item->signal_height_changed().connect(sigc::mem_fun(
	    this, &AudioTrackViewItem::on_track_canvas_item_height_changed));
}

TrackListItem* AudioTrackViewItem::get_track_list_item()
{
	return m_audio_track_list_item.get();
}

Glib::RefPtr<TrackCanvasItem> AudioTrackViewItem::get_track_canvas_item()
{
	return Glib::RefPtr<TrackCanvasItem>::cast_dynamic(m_audio_track_canvas_item);
}

void AudioTrackViewItem::on_track_canvas_item_height_changed()
{
	m_audio_track_list_item->set_height(m_audio_track_canvas_item->get_height());
}

} // namespace ui
