
#include <ui/edit_window.hpp>

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
	// or perhaps ProjectView destructor?
	gtk_main_quit();
}

} // anonymous namespace


namespace gmojo {

EditWindow::EditWindow(boost::shared_ptr<mojo::Project> project)
	:
		m_project(project),
		m_edit_window(0),
		m_ui_manager(gtk::ui_manager_factory()),
		m_menu_bar(m_ui_manager),
		m_edit_canvas(project)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// check return
	m_edit_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	gtk_window_set_default_size (GTK_WINDOW (m_edit_window), 640, 480);
	gtk_widget_show (m_edit_window);

	// check return
	GtkWidget* edit_window_vbox = gtk_vbox_new(false, 0);

	// pack main vbox
	gtk_box_pack_start (GTK_BOX (edit_window_vbox),
						m_edit_canvas.widget(),
						true, true, 0);

	gtk_box_pack_start (GTK_BOX (edit_window_vbox),
						m_menu_bar.widget(),
						true, true, 0);

	// pack main vbox in window
	gtk_container_add (GTK_CONTAINER (m_edit_window), edit_window_vbox);

	// connect signals
	g_signal_connect (G_OBJECT (m_edit_window), "delete_event",
			G_CALLBACK (on_delete_event), this);

	g_signal_connect (G_OBJECT (m_edit_window), "destroy",
			G_CALLBACK (on_destroy), this);

	
}

EditWindow::~EditWindow()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
}

} // namespace gmojo
