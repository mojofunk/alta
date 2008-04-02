
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <ui/widget.hpp>
#include <ui/widget_ptr.hpp>

namespace gmojo {

class Project;

/**
 * does the EditWindow need to keep a reference to the project?
 */
class EditWindow : public Widget
{
public: // constructors

	EditWindow(Project* project);

	~EditWindow();

public: // widget interface

	virtual GtkWidget* get_widget () const
	{ return m_window; }

private: // methods 

	bool add_action_groups_to_ui_manager ();

	void merge_ui_definitions ();

	void create_menu_bar ();

	void pack_widgets();
	
	void setup_window ();

private: // event handlers

	static gboolean delete_event_handler (GtkWidget*, GdkEvent*,
			gpointer edit_window);

	bool on_delete_event ();

private: // member data

	Project* m_project;

	GtkWidget* m_window;
	GtkUIManager* m_ui_manager;

	GtkWidget* m_main_vbox;
	GtkWidget* m_menu_bar;
	
	WidgetSPtr m_transport_toolbar;
	WidgetSPtr m_track_view;
	WidgetSPtr m_status_bar;

};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
