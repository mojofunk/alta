
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <boost/noncopyable.hpp>

#include <gtk/gtk.h>
#include <goocanvas.h>

#include <libmojo/project.hpp>

#include "edit_canvas.hpp"

namespace gmojo {

class EditWindow : boost::noncopyable
{
public:

	EditWindow(boost::shared_ptr<mojo::Project> project);

	~EditWindow();

private:

	boost::shared_ptr<mojo::Project> m_project;

	GtkWidget* m_edit_window;

	EditCanvas m_edit_canvas;
};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
