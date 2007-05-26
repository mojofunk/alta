
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <boost/noncopyable.hpp>

#include <gtk/gtk.h>
#include <goocanvas.h>

#include <libmojo/project.hpp>

#include <ui/gtk_ui_manager.hpp>
#include <ui/edit_window_menu_bar.hpp>
#include <ui/edit_canvas.hpp>

namespace gmojo {

class EditWindow : boost::noncopyable
{
public:

	EditWindow(boost::shared_ptr<mojo::Project> project);

	~EditWindow();

private:

	boost::shared_ptr<mojo::Project> m_project;

	GtkWidget* m_edit_window;

	boost::intrusive_ptr<GtkUIManager> m_ui_manager;

	//EditWindowActions m_actions;

	EditWindowMenuBar m_menu_bar;

	EditCanvas m_edit_canvas;
};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
