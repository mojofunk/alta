
#include "app.hpp"
#include "project_window.hpp"
#include "utils.hpp"
#include "transport_toolbar.hpp"
#include "track_view_factory.hpp"

namespace ui {

ProjectWindow::ProjectWindow (mojo::Project* proj)
	: m_project(proj)
	, m_transport_toolbar (Gtk::manage (new TransportToolbar(proj)))
	, m_track_view (Gtk::manage (TrackViewFactory::create (proj)))
{
	const std::string ui_file = "data/project_window.ui";

	m_builder = Gtk::Builder::create_from_file (ui_file);

	m_builder->get_widget ("project-window", m_window);

	connect_file_menu_actions ();

	connect_project_menu_actions ();

	connect_view_menu_actions ();

	pack_transport ();

	m_window->signal_delete_event().connect
		(sigc::mem_fun (this, &ProjectWindow::on_delete_event));

	m_window->show_all ();
}

void
ProjectWindow::connect_file_menu_actions ()
{
	connect_action (m_builder, "project-new-action",
		   	sigc::ptr_fun (App::new_project));

	connect_action (m_builder, "project-open-action",
		   	sigc::ptr_fun (App::open_project));

	connect_action (m_builder, "project-save-action",
			sigc::bind (sigc::ptr_fun (&App::save_project), m_project));

	connect_action (m_builder, "open-preferences-action",
			sigc::ptr_fun (&App::open_preferences_dialog));

	connect_action (m_builder, "import-audio-action",
			sigc::ptr_fun (&App::open_import_dialog));

	connect_action (m_builder, "project-close-action",
		   	sigc::bind (sigc::ptr_fun (&App::close_project), m_project));

	connect_action (m_builder, "app-quit-action",
		   	sigc::ptr_fun (App::quit));
}

void
ProjectWindow::connect_project_menu_actions ()
{
	connect_action (m_builder, "audio-track-add-action",
			sigc::bind (sigc::ptr_fun (&App::add_track), m_project));

	connect_action (m_builder, "project-setup-action",
			sigc::bind (sigc::ptr_fun (&App::open_project_setup_dialog), m_project));
}

void
ProjectWindow::connect_view_menu_actions ()
{
	connect_toggleaction (m_builder, "project-window-fullscreen-toggleaction",
	   	sigc::mem_fun (this, &ProjectWindow::on_fullscreen_toggled));
}

void
ProjectWindow::pack_transport ()
{
	Gtk::VBox* vbox1 = 0;

	m_builder->get_widget ("vbox1", vbox1);

	vbox1->pack_start (*m_transport_toolbar, false, false);
	vbox1->reorder_child (*m_transport_toolbar, 1);

	vbox1->pack_start (*m_track_view, true, true);
	vbox1->reorder_child (*m_track_view, 2);

}

ProjectWindow::~ProjectWindow ()
{
	delete m_window;
}

bool
ProjectWindow::on_delete_event (GdkEventAny*)
{
	App::close_project (m_project);
	return true;
}

void
ProjectWindow::on_fullscreen_toggled ()
{
	ToggleActionPtr action = get_toggleaction (m_builder, "project-window-fullscreen-toggleaction");

	if (action->get_active ())
		m_window->fullscreen ();
	else
		m_window->unfullscreen ();
}

} // namespace ui