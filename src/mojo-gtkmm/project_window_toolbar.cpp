
#include "project_window_toolbar.hpp"

#include "transport_toolbar.hpp"

namespace ui {

ProjectWindowToolbar::ProjectWindowToolbar (mojo::Project* p)
	: m_project(p)
	, m_activate_project_button("Activate Project")
{
	pack_start (m_activate_project_button, false, false);

	Gtk::HBox *ttb = Gtk::manage (new TransportToolbar(p));
	pack_start (*ttb, false, false);

}

}
