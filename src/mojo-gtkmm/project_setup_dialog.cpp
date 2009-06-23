#include <cassert>

#include "project_setup_dialog.hpp"

#include "log.hpp"

namespace ui {

ProjectSetupDialog::ProjectSetupDialog (mojo::Project* proj)
	: m_project(proj)
{
	const std::string ui_file = "data/project_setup.ui";

	m_builder = Gtk::Builder::create_from_file (ui_file);

	m_builder->get_widget ("projectsetup", m_window);

}

ProjectSetupDialog::~ProjectSetupDialog ()
{
	delete m_window;
}

int
ProjectSetupDialog::run ()
{
	LOG;
	return m_window->run();
}

} // namespace ui
