
#include <ui/edit_canvas.hpp>

#include <ui/debug/debug.hpp>

namespace gmojo {



EditCanvas::EditCanvas(mojo::Project* project)
	:
		m_project(project)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// take reference to project?

	create_scrolled_window ();
	create_canvas ();
	create_track_control_list ();
	create_packing_widgets ();
	pack_widgets ();
	connect_signals ();

	gtk_widget_show_all (m_hpaned);

}

EditCanvas::~EditCanvas()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

void
EditCanvas::destroy ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

void
EditCanvas::dispose ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	
}

bool
EditCanvas::create_scrolled_window ()
{
	m_scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (m_scrolled_window),
			GTK_SHADOW_IN);

	return true;
}

bool
EditCanvas::create_canvas ()
{
	m_canvas = goo_canvas_new ();
	m_root_item = goo_canvas_get_root_item (GOO_CANVAS (m_canvas));

	gtk_widget_set_size_request (m_canvas, 600, 450);
	goo_canvas_set_bounds (GOO_CANVAS (m_canvas), 0, 0, 1000, 1000);

	return true;
}

bool
EditCanvas::create_track_control_list ()
{
	m_label = gtk_label_new("Track Control List");

	return true;
}

bool
EditCanvas::create_packing_widgets ()
{
	m_hpaned = gtk_hpaned_new ();

	return true;
}

void
EditCanvas::pack_widgets ()
{
	// add canvas to scrolled window
	gtk_container_add (GTK_CONTAINER (m_scrolled_window), m_canvas);

	// pack horizontal paned
	gtk_paned_pack1(GTK_PANED (m_hpaned), m_label, TRUE, TRUE);
	gtk_paned_pack2(GTK_PANED (m_hpaned), m_scrolled_window, TRUE, TRUE);
}

void
EditCanvas::connect_signals ()
{
	/* Connect a signal handlers for the root canvas item. */
	g_signal_connect (m_root_item, "button_press_event",
			(GtkSignalFunc) public_on_root_button_press, this);
}

gboolean
EditCanvas::public_on_root_button_press (GooCanvasItem  *view,
		GooCanvasItem  *target,
		GdkEventButton *event,
		gpointer        data)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	EditCanvas* edit_canvas = static_cast<EditCanvas*>(data);

	return edit_canvas->on_root_button_press(view, target, event);
}

bool
EditCanvas::on_root_button_press (GooCanvasItem  *view,
		GooCanvasItem  *target,
		GdkEventButton *event)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	return true;
}
} // namespace gmojo
