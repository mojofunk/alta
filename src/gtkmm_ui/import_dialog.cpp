
#include "import_dialog.hpp"

#include "log.hpp"
#include "filesystem_paths.hpp"

namespace ui {

ImportDialog::ImportDialog()
{
	LOG;

	try {
		m_builder =
		    Gtk::Builder::create_from_file(get_ui_filepath("import_dialog.ui"));
	}
	catch (const Glib::FileError& ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return;
	}
	catch (const Gtk::BuilderError& ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return;
	}

	m_builder->get_widget("import-dialog", m_dialog);
}

ImportDialog::~ImportDialog()
{
	delete m_dialog;
}

int ImportDialog::run()
{
	LOG;
	return m_dialog->run();
}

} // namespace ui
