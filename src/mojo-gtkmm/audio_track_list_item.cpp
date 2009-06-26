#include "audio_track_list_item.hpp"

namespace ui {

AudioTrackListItem::AudioTrackListItem (mojo::Track* t)
	: m_track(t)
{
	m_track_name.set_text("Track Name");
	m_track_name.show();
	pack_start(m_track_name);
	show();
}

void
AudioTrackListItem::set_height ()
{

}

uint32_t
AudioTrackListItem::get_height () const
{

}

void
AudioTrackListItem::set_selected (bool)
{

}

bool
AudioTrackListItem::get_selected () const
{

}

} // namespace ui
