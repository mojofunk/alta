

#include <ui/application_actions.hpp>
#include <ui/edit_window.hpp>
#include <ui/edit_window_ui_defs.hpp>

#include "debug.hpp"


namespace gmojo {

EditWindow::EditWindow(boost::shared_ptr<mojo::Project> project)
	:
		m_project(project),
		m_ui_manager(0),
		m_window(0),
		m_main_vbox(0),
		m_menu_bar(0),
		m_edit_canvas(project)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	create_window();

	create_packing_widgets();

	create_ui_manager();

	create_menu_bar();

	pack_widgets();

	connect_signals();

}

EditWindow::~EditWindow()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	g_object_unref(m_ui_manager);

}

bool
EditWindow::create_window()
{
	// check return
	m_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	gtk_window_set_default_size (GTK_WINDOW (m_window), 640, 480);
	gtk_widget_show (m_window);
	
	return true;
}

bool
EditWindow::create_packing_widgets()
{
	// check return
	m_main_vbox = gtk_vbox_new(false, 0);
	gtk_widget_show (m_main_vbox);

	return true;
}

bool
EditWindow::create_ui_manager()
{
	m_ui_manager = gtk_ui_manager_new();

	// add ui_manager accel group to window
	gtk_window_add_accel_group (GTK_WINDOW (m_window),
			gtk_ui_manager_get_accel_group (m_ui_manager));

	// do something better here
	GtkActionGroup* app_action_group = gtk_action_group_new ("ApplicationActions");
	//gtk_action_group_set_translation_domain (app_action_group, NULL);

	gtk_action_group_add_actions (app_action_group,
			application_action_entries,
			G_N_ELEMENTS (application_action_entries),
			&Application::instance());

	gtk_ui_manager_insert_action_group (m_ui_manager, app_action_group, 0);
	
	// m_ui_manager now holds the only reference
	g_object_unref (app_action_group);

	guint merge_id = 0;
	GError * error = NULL;

	merge_id = gtk_ui_manager_add_ui_from_string (m_ui_manager,
			edit_menu_ui_defs, -1, &error);

	if (merge_id == 0) {
		
#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL << error->message;
#endif

		g_error_free(error);
		
		// throw 
	}

	return true;
}

bool
EditWindow::create_menu_bar()
{

	m_menu_bar = gtk_ui_manager_get_widget(m_ui_manager, "/MainMenuBar");
	
	if(!m_menu_bar)
	{

#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL;
#endif

		return false;
	}
	return true;
}

void
EditWindow::pack_widgets()
{
	// pack main vbox
	gtk_box_pack_start (GTK_BOX (m_main_vbox),
						m_menu_bar,
						false, false, 0);
	
	gtk_box_pack_start (GTK_BOX (m_main_vbox),
						m_edit_canvas.widget(),
						true, true, 0);


	// pack main vbox in window
	gtk_container_add (GTK_CONTAINER (m_window), m_main_vbox);
}

void
EditWindow::connect_signals()
{
	// connect signals
	g_signal_connect (G_OBJECT (m_window), "delete_event",
			G_CALLBACK (EditWindow::on_edit_window_delete_event), this);

	g_signal_connect (G_OBJECT (m_window), "destroy",
			G_CALLBACK (EditWindow::on_edit_window_destroy), this);
}

gboolean
EditWindow::on_edit_window_delete_event (GtkWidget* widget,
		GdkEvent* event, gpointer data )
{
	EditWindow* edit_window = static_cast<EditWindow*>(data);

	return edit_window->on_delete_event(widget, event);
}

bool
EditWindow::on_delete_event(GtkWidget* widget, GdkEvent* event)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// if projects state is modified, ask about saving.

	// causes signal_close signal to be emitted.
	// which will cause the Application class to
	// destroy the ProjectView which includes this window.
	// close_project();
	return FALSE;

}

void
EditWindow::on_edit_window_destroy (GtkWidget* widget, gpointer data)
{
	EditWindow* edit_window = static_cast<EditWindow*>(data);

	edit_window->on_destroy(widget);
}

void
EditWindow::on_destroy (GtkWidget* widget)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	// this should be in ProjectView::quit
	// or perhaps ProjectView destructor?
	gtk_main_quit();
}

} // namespace gmojo
