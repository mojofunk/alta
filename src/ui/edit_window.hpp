
#ifndef GMOJO_EDIT_WINDOW_INCLUDED
#define GMOJO_EDIT_WINDOW_INCLUDED

#include <boost/noncopyable.hpp>

#include <gtk/gtk.h>

#include <libmojo/project.hpp>


namespace gmojo {

class EditWindow : boost::noncopyable
{
public:

	EditWindow(mojo::project project);

	~EditWindow();

private:

	mojo::project m_project;

	GtkWidget* m_edit_window;
};

} // namespace gmojo

#endif // GMOJO_EDIT_WINDOW_INCLUDED
