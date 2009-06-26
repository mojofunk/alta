
#include "audio_track_canvas_item.hpp"

namespace ui {

AudioTrackCanvasItem::AudioTrackCanvasItem (mojo::Track* audio_track)
	: m_audio_track(audio_track)
	, m_rect(Goocanvas::Rect::create(0, 0, 100, 100))
{
	add_child(m_rect);

	m_rect->property_line_width().set_value(10.0);
	m_rect->property_radius_x().set_value(20.0);
	m_rect->property_radius_y().set_value(20.0);
	m_rect->property_stroke_color().set_value("yellow");
	m_rect->property_fill_color().set_value("red");
}

Glib::RefPtr<AudioTrackCanvasItem>
AudioTrackCanvasItem::create (mojo::Track* track)
{
	return Glib::RefPtr<AudioTrackCanvasItem>(new AudioTrackCanvasItem(track));
}

void
AudioTrackCanvasItem::set_height ()
{

}

uint32_t
AudioTrackCanvasItem::get_height () const
{

}

void
AudioTrackCanvasItem::set_selected (bool)
{

}

bool
AudioTrackCanvasItem::get_selected () const
{

}

} // namespace ui
