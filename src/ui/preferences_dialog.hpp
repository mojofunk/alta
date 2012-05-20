
#ifndef UI_PREFERENCES_DIALOG
#define UI_PREFERENCES_DIALOG

#include "types.hpp"

namespace ui {

class PreferencesDialog
{
public:

	PreferencesDialog ();

	~PreferencesDialog ();

	int run ();

private:

	BuilderGPtr m_builder;

	Gtk::Dialog* m_dialog;

};

} // namespace ui

#endif
