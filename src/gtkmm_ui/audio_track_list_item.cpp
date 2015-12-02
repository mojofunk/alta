namespace ui {

AudioTrackListItem::AudioTrackListItem(mojo::Track* t)
    : m_track(t)
{
	m_track_name.set_text("Track Name");
	m_track_name.show();
	pack_start(m_track_name);
	show();
}

void AudioTrackListItem::set_height(uint32_t height)
{
	if (get_height() == height) return;

	property_height_request() = height;
	m_signal_height_changed();
}

uint32_t AudioTrackListItem::get_height() const
{
	return get_allocation().get_height();
}

void AudioTrackListItem::set_selected(bool)
{
}

bool AudioTrackListItem::get_selected() const
{
}

} // namespace ui
