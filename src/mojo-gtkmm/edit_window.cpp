
#include "project.hpp"
#include "app.hpp"
#include "edit_window.hpp"
#include "utils.hpp"
#include "transport_toolbar_factory.hpp"
#include "track_view_factory.hpp"

namespace ui {

EditWindow::EditWindow (Project* proj)
	: m_project(proj)
	, m_transport_toolbar (Gtk::manage (TransportToolbarFactory::create (proj)))
	, m_track_view (Gtk::manage (TrackViewFactory::create (proj)))
{
	const std::string ui_file = "data/gmojo.ui";

	m_builder = Gtk::Builder::create_from_file (ui_file);

	m_builder->get_widget ("editwindow", m_window);

	connect_file_menu_actions ();

	connect_project_menu_actions ();

	connect_view_menu_actions ();

	pack_transport ();

	m_window->signal_delete_event().connect
		(sigc::mem_fun (this, &EditWindow::on_delete_event));

	m_window->show_all ();
}

void
EditWindow::connect_file_menu_actions ()
{
	connect_action (m_builder, "new-project-menuitem",
		   	sigc::ptr_fun (App::new_project));

	connect_action (m_builder, "open-project-menuitem",
		   	sigc::ptr_fun (App::open_project));

	connect_action (m_builder, "save-project-menuitem",
		   	sigc::mem_fun (m_project, &Project::save));

	connect_action (m_builder, "close-project-menuitem",
		   	sigc::bind (sigc::ptr_fun (&App::close_project), m_project));

	connect_action (m_builder, "quit-menuitem",
		   	sigc::ptr_fun (App::quit));
}

void
EditWindow::connect_project_menu_actions ()
{
	connect_action (m_builder, "add-audio-track-menuitem",
		   	sigc::mem_fun (m_project, &Project::create_audio_track));
}

void
EditWindow::connect_view_menu_actions ()
{
	connect_toggleaction (m_builder, "fullscreen-menuitem", 
	   	sigc::mem_fun (this, &EditWindow::on_fullscreen_toggled));
}

void
EditWindow::pack_transport ()
{
	Gtk::VBox* vbox1 = 0;

	m_builder->get_widget ("vbox1", vbox1);

	vbox1->pack_start (*m_transport_toolbar, false, false);
	vbox1->reorder_child (*m_transport_toolbar, 1);

	vbox1->pack_start (*m_track_view, true, true);
	vbox1->reorder_child (*m_track_view, 2);

}

EditWindow::~EditWindow ()
{
	delete m_window;
}

bool
EditWindow::on_delete_event (GdkEventAny*)
{
	App::close_project (m_project);
	return true;
}

void
EditWindow::on_fullscreen_toggled ()
{
	ToggleActionPtr action = get_toggleaction (m_builder, "fullscreen-menuitem");

	if (action->get_active ())
		m_window->fullscreen ();
	else
		m_window->unfullscreen ();
}

} // namespace ui
