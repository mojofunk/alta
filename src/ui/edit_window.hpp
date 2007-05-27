
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <gtk/gtk.h>
#include <goocanvas.h>

#include <boost/noncopyable.hpp>

#include <libmojo/project.hpp>

#include <ui/edit_canvas.hpp>

namespace gmojo {

class EditWindow : boost::noncopyable
{
public:

	EditWindow(boost::shared_ptr<mojo::Project> project);

	~EditWindow();

private:

	bool create_window ();

	bool create_packing_widgets ();

	bool create_ui_manager();

	bool add_action_groups_to_ui_manager ();

	bool merge_ui_definitions ();

	bool create_menu_bar ();

	//bool create_edit_canvas();

	void pack_widgets();

	void connect_signals();

private:

	// static signal handlers
	
	static gboolean on_edit_window_delete_event(GtkWidget*, GdkEvent*,
				gpointer edit_window);

	static void on_edit_window_destroy(GtkWidget*, gpointer edit_window);

	// instance signal handlers
	
	// ask about saving and possibly close project
	bool on_delete_event(GtkWidget*, GdkEvent*);

	// no sure what to do on_destroy, possibly nothing.
	void on_destroy(GtkWidget*);

private:

	boost::shared_ptr<mojo::Project> m_project;
	
	// gobjects
	GtkUIManager* m_ui_manager;

	// widgets
	GtkWidget* m_window;

	GtkWidget* m_main_vbox;

	GtkWidget* m_menu_bar;


	EditCanvas m_edit_canvas;
};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
