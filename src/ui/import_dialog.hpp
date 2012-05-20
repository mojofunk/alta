
#ifndef UI_IMPORT_DIALOG
#define UI_IMPORT_DIALOG

#include "types.hpp"

namespace ui {

class ImportDialog
{
public:

	ImportDialog ();

	~ImportDialog ();

	int run ();

private:

	BuilderPtr m_builder;

	Gtk::Dialog* m_dialog;
};

} // namespace ui

#endif
