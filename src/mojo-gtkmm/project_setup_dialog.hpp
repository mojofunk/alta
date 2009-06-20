
#ifndef UI_PROJECT_SETUP_DIALOG
#define UI_PROJECT_SETUP_DIALOG

#include "types.hpp"

#include <mojo/mojo.hpp>

namespace ui {

class ProjectSetupDialog
{
public:

	ProjectSetupDialog (mojo::Project* proj);

	~ProjectSetupDialog ();

	int run ();

private:

	mojo::Project* m_project;

	BuilderPtr m_builder;

	Gtk::Dialog* m_window;

};

} // namespace ui

#endif
