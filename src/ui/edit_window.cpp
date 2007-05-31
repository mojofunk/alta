
#include <boost/bind.hpp>

#include <ui/edit_window.hpp>

#include <ui/edit_window_menu_action_group.hpp>
#include <ui/application_action_group.hpp>
#include <ui/project_action_group.hpp>

#include <ui/edit_window_menu_ui_definition.hpp>

#include <ui/debug/debug.hpp>


namespace gmojo {

EditWindow::EditWindow(mojo::Project* project)
	:
		m_project(project),
		m_ui_manager(0),
		m_window(0),
		m_main_vbox(0),
		m_menu_bar(0),
		m_edit_canvas(0)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_project->ref();
	
	m_project->signal_destroy().connect
		(
		 boost::bind (
			 boost::mem_fn (&EditWindow::on_project_signal_destroy),
			 this)
		);

	create_window ();

	create_packing_widgets ();

	create_ui_manager ();

	add_action_groups_to_ui_manager ();

	merge_ui_definitions ();

	create_menu_bar ();

	create_edit_canvas ();

	pack_widgets ();

	connect_signals ();

}

EditWindow::~EditWindow()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

void
EditWindow::destroy ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	//destroy the window
	gtk_widget_destroy (GTK_WIDGET (m_window));
}

void
EditWindow::dispose ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	
	if (m_project) m_project->unref();
	
	g_object_unref (m_ui_manager);

	m_edit_canvas->unref ();
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
EditWindow::create_packing_widgets ()
{
	// check return
	m_main_vbox = gtk_vbox_new (false, 0);
	gtk_widget_show (m_main_vbox);

	return true;
}

bool
EditWindow::create_ui_manager()
{
	m_ui_manager = gtk_ui_manager_new ();

	if(!m_ui_manager)
	{

#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL;
#endif

		return false;
	}

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
	action_group = application_action_group_new(&Application::instance());
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
		
#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL << error->message;
#endif

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

#ifdef GMOJO_DEBUG
		LOG_GMOJO_CRITICAL;
#endif

		return false;
	}
	return true;
}

bool
EditWindow::create_edit_canvas ()
{
	m_edit_canvas = new EditCanvas(m_project);

	if(!m_edit_canvas)
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
						m_edit_canvas->widget(),
						true, true, 0);

	// pack main vbox in window
	gtk_container_add (GTK_CONTAINER (m_window), m_main_vbox);
}

void
EditWindow::connect_signals()
{
	// connect to window signals so we can propogate them
	// using boost::signal
	g_signal_connect (G_OBJECT (m_window), "delete_event",
			G_CALLBACK (EditWindow::on_window_delete_event), this);
	
	g_signal_connect (G_OBJECT (m_window), "destroy",
			G_CALLBACK (EditWindow::on_window_destroy), this);
}

gboolean
EditWindow::on_window_delete_event (GtkWidget* widget,
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

	g_assert (widget == m_window);

	return m_signal_delete_event ();
}

void
EditWindow::on_window_destroy (GtkWidget* widget, gpointer window)
{
	EditWindow* edit_window = static_cast<EditWindow*>(window);

	return edit_window->on_destroy (widget);
}

void
EditWindow::on_destroy (GtkWidget* widget)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	g_assert (widget == m_window);

	m_signal_destroy ();

	m_window = 0;
}

void
EditWindow::on_project_signal_destroy ()
{
	// disconnect signals connected to project

	m_project->unref ();
	m_project = 0;

}

} // namespace gmojo
