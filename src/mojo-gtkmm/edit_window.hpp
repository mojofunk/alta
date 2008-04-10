
#ifndef UI_EDIT_WINDOW
#define UI_EDIT_WINDOW

#include "types.hpp"

namespace ui {

class Project;

class EditWindow
{
public:

	EditWindow (Project* proj);
	
	~EditWindow ();

private:

	bool on_delete_event (GdkEventAny*);

	void on_fullscreen_toggled ();

private:

	Project* m_project;

	BuilderPtr m_builder;

	Gtk::Window* m_window;
};

} // namespace ui

#endif
