
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <mojo/project_ptr.hpp>

#include <ui/gtk/window.hpp>
#include <ui/gtk/widget_ptr.hpp>

namespace gmojo {

class EditWindow : public gtk::Window
{
public:

	EditWindow(mojo::ProjectSPtr project);

	~EditWindow();

private:

	bool add_action_groups_to_ui_manager ();

	bool merge_ui_definitions ();

	bool create_menu_bar ();

	void pack_widgets();
	
	void setup_window ();

private:

	mojo::ProjectSPtr m_project;

	// gobjects
	GtkUIManager* m_ui_manager;

	GtkWidget* m_main_vbox;
	GtkWidget* m_menu_bar;

	gtk::WidgetSPtr m_track_view;

};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
