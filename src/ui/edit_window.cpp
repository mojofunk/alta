
#include "edit_window.hpp"

#include "debug.hpp"

namespace {

gboolean
on_delete_event (GtkWidget* widget, GdkEvent* event, gpointer data )
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// if projects state is modified, ask about saving.
	return FALSE;
}

void
on_destroy (GtkWidget* widget, gpointer)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	// this should be in ProjectView::quit
	gtk_main_quit();
}

} // anonymous namespace


namespace gmojo {

EditWindow::EditWindow(mojo::project project)
	:
		m_project(project),
		m_edit_canvas(project)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_edit_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	gtk_window_set_default_size (GTK_WINDOW (m_edit_window), 640, 480);
	gtk_widget_show (m_edit_window);

	g_signal_connect (G_OBJECT (m_edit_window), "delete_event",
			G_CALLBACK (on_delete_event), this);

	g_signal_connect (G_OBJECT (m_edit_window), "destroy",
			G_CALLBACK (on_destroy), this);

	gtk_container_add (GTK_CONTAINER (m_edit_window), m_edit_canvas.widget());

}

EditWindow::~EditWindow()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
}

} // namespace gmojo
