
#include <ui/edit_window.hpp>

#include <ui/track_view.hpp>
#include <ui/transport_toolbar.hpp>
#include <ui/status_bar.hpp>

#include <ui/actions/edit_window_menu_action_group.hpp>
#include <ui/actions/app_action_group.hpp>
#include <ui/actions/project_action_group.hpp>

#include <ui/edit_window_menu_ui_definition.hpp>

namespace gmojo {

EditWindow::EditWindow(Project* project)
	:
		m_project(project)
		, m_window (gtk_window_new (GTK_WINDOW_TOPLEVEL))
		, m_ui_manager(gtk_ui_manager_new ())
		, m_main_vbox(gtk_vbox_new (false, 0))
		, m_menu_bar(0)
		, m_transport_toolbar(new TransportToolbar)
		, m_track_view(new TrackView(project))
		, m_status_bar(new StatusBar)
{
	add_action_groups_to_ui_manager ();

	merge_ui_definitions ();

	create_menu_bar ();

	pack_widgets ();

	setup_window ();

	g_signal_connect (G_OBJECT (m_window), "delete-event",
			G_CALLBACK (EditWindow::delete_event_handler), this);
}

EditWindow::~EditWindow()
{
	gtk_widget_destroy (GTK_WIDGET (m_window));
	g_object_unref (m_ui_manager);
}

gboolean
EditWindow::delete_event_handler (GtkWidget* widget,
		GdkEvent* event, gpointer data )
{
	EditWindow* window = static_cast<EditWindow*>(data);
	return window->on_delete_event ();
}

bool
EditWindow::on_delete_event ()
{
	App::close_project (m_project);
	return true;
}

bool
EditWindow::add_action_groups_to_ui_manager ()
{
	GtkActionGroup * action_group = 0;

	// add ui_manager accel group to window
	gtk_window_add_accel_group (GTK_WINDOW (m_window),
			gtk_ui_manager_get_accel_group (m_ui_manager));

	// add top level menu actions
	action_group = edit_window_menu_action_group_new();
	gtk_ui_manager_insert_action_group (m_ui_manager, action_group, 0);
	g_object_unref (action_group);
	
	// add application actions
	action_group = app_action_group_new();
	gtk_ui_manager_insert_action_group (m_ui_manager, action_group, 0);
	g_object_unref (action_group);

	// add project actions
	action_group = project_action_group_new(m_project);
	gtk_ui_manager_insert_action_group (m_ui_manager, action_group, 0);
	g_object_unref (action_group);

	return true;
}

bool
EditWindow::merge_ui_definitions ()
{
	guint merge_id = 0;
	GError * error = NULL;

	merge_id = gtk_ui_manager_add_ui_from_string (m_ui_manager,
			edit_window_menu_ui_definition, -1, &error);

	if (merge_id == 0) {

		g_error_free(error);
	
		return false;
	}

	return true;
}

bool
EditWindow::create_menu_bar()
{

	m_menu_bar = gtk_ui_manager_get_widget(m_ui_manager, "/MainMenuBar");
	
	if(!m_menu_bar)
	{
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
			m_transport_toolbar->get_widget (),
			false, false, 0);

	gtk_box_pack_start (GTK_BOX (m_main_vbox),
			m_track_view->get_widget (),
			true, true, 0);

	gtk_box_pack_start (GTK_BOX (m_main_vbox),
			m_status_bar->get_widget (),
			false, false, 0);

	// pack main vbox in window
	gtk_container_add (GTK_CONTAINER (m_window), m_main_vbox);
}

void
EditWindow::setup_window()
{
	gtk_window_set_default_size (GTK_WINDOW (m_window), 640, 480);
	gtk_widget_show_all (m_window);
}

} // namespace gmojo
