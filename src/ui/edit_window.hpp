
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <gtk/gtk.h>

#include <libmojo/object.hpp>
#include <libmojo/project.hpp>

#include <ui/edit_canvas.hpp>

namespace gmojo {

class EditWindow : public mojo::Object
{
public:

	EditWindow(mojo::Project* project);

	// wrap gtk_widget_destroy (window)
	virtual void destroy ();

	boost::signal<bool ()>& signal_delete_event ()
	{ return m_signal_delete_event; }

protected:

	~EditWindow();

	virtual void dispose ();

	boost::signal<bool ()> m_signal_delete_event;

private:

	bool create_window ();

	bool create_packing_widgets ();

	bool create_ui_manager();

	bool add_action_groups_to_ui_manager ();

	bool merge_ui_definitions ();

	bool create_menu_bar ();

	bool create_edit_canvas();

	void pack_widgets();

	void connect_signals();

private:

	static gboolean on_window_delete_event(GtkWidget*, GdkEvent*,
				gpointer edit_window);

	bool on_delete_event(GtkWidget*, GdkEvent*);


	static void on_window_destroy(GtkWidget*, gpointer edit_window);

	void on_destroy(GtkWidget*);

private:

	void on_project_signal_destroy ();

private:

	mojo::Project* m_project;
	
	// gobjects
	GtkUIManager* m_ui_manager;

	// widgets
	GtkWidget* m_window;

	GtkWidget* m_main_vbox;

	GtkWidget* m_menu_bar;

	EditCanvas* m_edit_canvas;

};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
