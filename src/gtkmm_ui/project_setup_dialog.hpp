
#ifndef UI_PROJECT_SETUP_DIALOG
#define UI_PROJECT_SETUP_DIALOG

#include "types.hpp"

namespace ui {

class ProjectSetupDialog {
public:
	ProjectSetupDialog(mojo::Project* proj);

	~ProjectSetupDialog();

	int run();

private:
	mojo::Project* m_project;

	BuilderGPtr m_builder;

	Gtk::Dialog* m_window;
};

} // namespace ui

#endif
