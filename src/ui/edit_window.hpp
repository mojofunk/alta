
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <mojo/project.hpp>

#include <ui/gtk/window.hpp>

#include <ui/track_view.hpp>

namespace gmojo {

class EditWindow : public gtk::Window
{
public:

	EditWindow(mojo::Project::ptr project);

	~EditWindow();

private:

	bool add_action_groups_to_ui_manager ();

	bool merge_ui_definitions ();

	bool create_menu_bar ();

	void pack_widgets();
	
	void setup_window ();

private:

	mojo::Project::ptr m_project;

	// gobjects
	GtkUIManager* m_ui_manager;

	GtkWidget* m_main_vbox;
	GtkWidget* m_menu_bar;

	TrackView m_track_view;

};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
