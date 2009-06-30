
#include "import_dialog.hpp"

#include "log.hpp"

namespace ui {

ImportDialog::ImportDialog ()
{
	LOG;
	const std::string ui_file = "data/import_dialog.ui";

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

	m_builder->get_widget ("import-dialog", m_dialog);
}

ImportDialog::~ImportDialog ()
{
	delete m_dialog;
}

int
ImportDialog::run ()
{
	LOG;
	return m_dialog->run();
}

} // namespace ui
