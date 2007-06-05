
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <gtk/gtk.h>

#include <mojo/project.hpp>

#include <ui/edit_canvas.hpp>

namespace gmojo {

class EditWindow
{
public:
	
	typedef boost::shared_ptr<EditWindow> ptr;

	typedef boost::signal<bool ()> delete_signal_t;
	typedef boost::signals::connection  connection_t;

public:

	EditWindow(mojo::Project::ptr project);

	~EditWindow();

	connection_t on_delete_event (const delete_signal_t::slot_type& handler)
	{ return m_signal_delete_event.connect(handler); }

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

private:

	mojo::Project::ptr m_project;

	// signals
	delete_signal_t m_signal_delete_event;

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
