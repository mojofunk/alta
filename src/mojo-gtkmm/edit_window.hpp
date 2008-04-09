
#ifndef UI_EDIT_WINDOW
#define UI_EDIT_WINDOW

#include <gtk/gtk.h>

namespace Gtk {
	class Window;
}

namespace ui {

class Project;

class EditWindow
{
public:

	EditWindow (Project* proj);
	
	~EditWindow ();

private:

	bool on_delete_event (GdkEventAny*);

private:

	Project* m_project;

	Gtk::Window* m_window;

};

} // namespace ui

#endif
