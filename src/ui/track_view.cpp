
#include <ui/track_view.hpp>

#include <ui/debug/debug.hpp>

namespace gmojo {



TrackView::TrackView(mojo::Project::ptr project)
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

TrackView::~TrackView()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

bool
TrackView::create_scrolled_window ()
{
	m_scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (m_scrolled_window),
			GTK_SHADOW_IN);

	return true;
}

bool
TrackView::create_canvas ()
{
	m_canvas = goo_canvas_new ();
	m_root_item = goo_canvas_get_root_item (GOO_CANVAS (m_canvas));

	gtk_widget_set_size_request (m_canvas, 600, 450);
	goo_canvas_set_bounds (GOO_CANVAS (m_canvas), 0, 0, 1000, 1000);

	return true;
}

bool
TrackView::create_track_control_list ()
{
	m_label = gtk_label_new("Track Control List");

	return true;
}

bool
TrackView::create_packing_widgets ()
{
	m_hpaned = gtk_hpaned_new ();

	return true;
}

void
TrackView::pack_widgets ()
{
	// add canvas to scrolled window
	gtk_container_add (GTK_CONTAINER (m_scrolled_window), m_canvas);

	// pack horizontal paned
	gtk_paned_pack1(GTK_PANED (m_hpaned), m_label, TRUE, TRUE);
	gtk_paned_pack2(GTK_PANED (m_hpaned), m_scrolled_window, TRUE, TRUE);
}

void
TrackView::connect_signals ()
{
	/* Connect a signal handlers for the root canvas item. */
	g_signal_connect (m_root_item, "button_press_event",
			(GtkSignalFunc) public_on_root_button_press, this);
}

gboolean
TrackView::public_on_root_button_press (GooCanvasItem  *view,
		GooCanvasItem  *target,
		GdkEventButton *event,
		gpointer        data)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	TrackView* track_view = static_cast<TrackView*>(data);

	return track_view->on_root_button_press(view, target, event);
}

bool
TrackView::on_root_button_press (GooCanvasItem  *view,
		GooCanvasItem  *target,
		GdkEventButton *event)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	return true;
}
} // namespace gmojo
