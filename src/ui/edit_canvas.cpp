
#include "edit_canvas.hpp"

#include "debug.hpp"

namespace gmojo {

gboolean
EditCanvas::public_on_rect_button_press (GooCanvasItem  *view,
		GooCanvasItem  *target,
		GdkEventButton *event,
		gpointer        data)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	EditCanvas* edit_canvas = static_cast<EditCanvas*>(data);

	return edit_canvas->on_rect_button_press(view, target, event);
}

bool
EditCanvas::on_rect_button_press (GooCanvasItem  *view,
		GooCanvasItem  *target,
		GdkEventButton *event)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	return true;
}


EditCanvas::EditCanvas(mojo::project project)
	:
		m_project(project)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (m_scrolled_window),
			GTK_SHADOW_IN);
	gtk_widget_show (m_scrolled_window);

	m_canvas = goo_canvas_new ();
	gtk_widget_set_size_request (m_canvas, 600, 450);
	goo_canvas_set_bounds (GOO_CANVAS (m_canvas), 0, 0, 1000, 1000);

	gtk_widget_show (m_canvas);
	gtk_container_add (GTK_CONTAINER (m_scrolled_window), m_canvas);

	m_root_item = goo_canvas_get_root_item (GOO_CANVAS (m_canvas));

	/* Add a few simple items. */
	m_rect_item = goo_canvas_rect_new (m_root_item, 100, 100, 400, 400,
			"line-width", 10.0,
			"radius-x", 20.0,
			"radius-y", 10.0,
			"stroke-color", "yellow",
			"fill-color", "red",
			NULL);

	m_text_item = goo_canvas_text_new (m_root_item, "Hello World", 300, 300, -1,
			GTK_ANCHOR_CENTER,
			"font", "Sans 24",
			NULL);

	goo_canvas_item_rotate (m_text_item, 45, 300, 300);

	/* Connect a signal handler for the rectangle item. */
	g_signal_connect (m_rect_item, "button_press_event",
			(GtkSignalFunc) public_on_rect_button_press, NULL);

}

EditCanvas::~EditCanvas()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
}

} // namespace gmojo
