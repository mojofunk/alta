
#ifndef UI_EDIT_WINDOW
#define UI_EDIT_WINDOW

#include <mojo/mojo.hpp>

#include "types.hpp"

namespace ui {

class TransportToolbar;
class TrackView;

class EditWindow
{
public:

	EditWindow (mojo::Project* proj);
	
	~EditWindow ();

private:

	void connect_file_menu_actions ();

	void connect_project_menu_actions ();

	void connect_view_menu_actions ();

	void pack_transport ();

private:

	bool on_delete_event (GdkEventAny*);

	void on_fullscreen_toggled ();

private:

	mojo::Project* m_project;

	BuilderPtr m_builder;

	Gtk::Window* m_window;

	TransportToolbar* m_transport_toolbar;

	TrackView* m_track_view;

};

} // namespace ui

#endif
