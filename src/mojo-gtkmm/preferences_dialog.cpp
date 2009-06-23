#include <cassert>

#include "preferences_dialog.hpp"

#include "log.hpp"

#include <iostream>

using namespace std;

namespace ui {

PreferencesDialog::PreferencesDialog ()
{
	LOG;
	const std::string ui_file = "data/preferences_dialog.ui";

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

	m_builder->get_widget ("preferences-dialog", m_dialog);
}

PreferencesDialog::~PreferencesDialog ()
{
	delete m_dialog;
}

int
PreferencesDialog::run ()
{
	LOG;
	return m_dialog->run();
}

} // namespace ui
