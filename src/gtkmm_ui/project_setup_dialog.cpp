#include <cassert>

#include "project_setup_dialog.hpp"
#include "filesystem_paths.hpp"

#include "log.hpp"

namespace ui {

ProjectSetupDialog::ProjectSetupDialog(mojo::Project* proj)
    : m_project(proj)
{
	try {
		m_builder =
		    Gtk::Builder::create_from_file(get_ui_filepath("project_setup.ui"));
	}
	catch (const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return;
	}
	catch (const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return;
	}

	m_builder->get_widget("projectsetup", m_window);
}

ProjectSetupDialog::~ProjectSetupDialog() { delete m_window; }

int ProjectSetupDialog::run()
{
	LOG;
	return m_window->run();
}

} // namespace ui
