#include <ui/canvas_item.hpp>

#include <iostream>

namespace gmojo {

CanvasItem::CanvasItem (GooCanvasItem* item, TrackCanvas* track_canvas)
	:
		m_item(item)
		, m_track_canvas(track_canvas) 
{
	g_signal_connect (G_OBJECT (m_item), "button-press-event",
			G_CALLBACK (CanvasItem::button_press_event_handler), this);

	g_signal_connect (G_OBJECT (m_item), "button-release-event",
			G_CALLBACK (CanvasItem::button_release_event_handler), this);

	g_signal_connect (G_OBJECT (m_item), "motion-notify-event",
			G_CALLBACK (CanvasItem::motion_notify_event_handler), this);

}

CanvasItem::~CanvasItem ()
{

}

gboolean
CanvasItem::button_press_event_handler (GooCanvasItem* item,
		GooCanvasItem* target_item, GdkEventButton* event,
		gpointer data)
{
	CanvasItem* canvas_item = static_cast<CanvasItem*>(data);

	return canvas_item->on_button_press_event (event);
}

gboolean
CanvasItem::button_release_event_handler (GooCanvasItem* item,
		GooCanvasItem* target_item, GdkEventButton* event,
		gpointer data)
{
	CanvasItem* canvas_item = static_cast<CanvasItem*>(data);

	return canvas_item->on_button_release_event (event);
}

gboolean
CanvasItem::motion_notify_event_handler (GooCanvasItem* item,
		GooCanvasItem* target_item, GdkEventMotion* event,
		gpointer data)
{
	CanvasItem* canvas_item = static_cast<CanvasItem*>(data);

	return canvas_item->on_motion_notify_event (event);
}

bool
CanvasItem::on_button_press_event (GdkEventButton* event)
{
	std::cerr << "button press" << std::endl;

	return true;
}

bool
CanvasItem::on_button_release_event (GdkEventButton* event)
{
	std::cerr << "button release" << std::endl;

	return true;
}

bool
CanvasItem::on_motion_notify_event (GdkEventMotion* event)
{
	std::cerr << "motion" << std::endl;

	return true;
}

} // namespace gmojo
