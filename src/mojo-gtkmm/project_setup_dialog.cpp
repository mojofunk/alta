#include <cassert>

#include "project_setup_dialog.hpp"

#include "log.hpp"

namespace ui {

ProjectSetupDialog::ProjectSetupDialog (mojo::Project* proj)
	: m_project(proj)
{
	const std::string ui_file = "data/project_setup.ui";

	try
	{
		m_builder = Gtk::Builder::create_from_file (ui_file);
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
		return;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return;
	}

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
