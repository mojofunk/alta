
#ifndef UI_EDIT_WINDOW
#define UI_EDIT_WINDOW

#include "types.hpp"

namespace ui {

class Project;
class TransportToolbar;

class EditWindow
{
public:

	EditWindow (Project* proj);
	
	~EditWindow ();

private:

	void connect_file_menu_actions ();

	void connect_project_menu_actions ();


private:

	bool on_delete_event (GdkEventAny*);

	void on_fullscreen_toggled ();

private:

	Project* m_project;

	BuilderPtr m_builder;

	Gtk::Window* m_window;

	TransportToolbar* m_transport_toolbar;

};

} // namespace ui

#endif
