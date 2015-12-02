namespace ui {

AudioTrackCanvasItem::AudioTrackCanvasItem(mojo::Track* audio_track)
    : m_audio_track(audio_track)
    , m_rect(Goocanvas::Rect::create(0, 0, 100, 100))
{
	add_child(m_rect);

	m_rect->property_line_width().set_value(1.0);
	m_rect->property_stroke_color().set_value("black");
	m_rect->property_fill_color().set_value("blue");
}

Glib::RefPtr<AudioTrackCanvasItem>
AudioTrackCanvasItem::create(mojo::Track* track)
{
	return Glib::RefPtr<AudioTrackCanvasItem>(new AudioTrackCanvasItem(track));
}

void AudioTrackCanvasItem::set_height(int height)
{
	if (property_height() == height) return;

	property_height() = height;
	m_rect->property_height() = height;
	m_signal_height_changed();
}

uint32_t AudioTrackCanvasItem::get_height() const
{
	return property_height();
}

void AudioTrackCanvasItem::set_width(int width)
{
	property_width() = width;
	m_rect->property_width() = width;
}

uint32_t AudioTrackCanvasItem::get_width() const
{
	return property_width();
}

void AudioTrackCanvasItem::set_selected(bool)
{
}

bool AudioTrackCanvasItem::get_selected() const
{
}

} // namespace ui
