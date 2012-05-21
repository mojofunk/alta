
#include "project_window_toolbar.hpp"

#include "app.hpp"
#include "session_event_handler.hpp"
#include "transport_toolbar.hpp"

#include "log.hpp"

namespace ui {

ProjectWindowToolbar::ProjectWindowToolbar (mojo::Project* p)
	: m_project(p)
	, m_activate_project_button("Activate Project")
{
	pack_start (m_activate_project_button, false, false);

	Gtk::HBox *ttb = Gtk::manage (new TransportToolbar(p));
	pack_start (*ttb, false, false);

	m_activate_project_button.signal_toggled().connect (sigc::mem_fun (this,
		&ProjectWindowToolbar::on_activate_project_button_toggled));

	App::get_session_event_handler().signal_active_project_changed().connect (sigc::mem_fun (this,
		&ProjectWindowToolbar::on_activate_project_changed));

}

void
ProjectWindowToolbar::on_activate_project_button_toggled ()
{
	if (m_activate_project_button.get_active())
	{
		App::get_session().set_active_project (m_project);
	}
	else
	{
		// not sure what to do here
	}
}

void
ProjectWindowToolbar::on_activate_project_changed (mojo::Project* p)
{
	LOG;

	m_activate_project_button.set_active (m_project == p);
}

} // namespace ui