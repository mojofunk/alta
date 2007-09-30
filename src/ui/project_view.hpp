
#ifndef GMOJO_PROJECT_VIEW_INCLUDED
#define GMOJO_PROJECT_VIEW_INCLUDED

#include <boost/shared_ptr.hpp>

#include <mojo/project_ptr.hpp>

#include <ui/gtk/window.hpp>

namespace gmojo {

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed. It also 
   manages the top level windows for a project
*/
class ProjectView
{
public:

	typedef boost::shared_ptr<ProjectView> ptr;
	typedef boost::weak_ptr<ProjectView> weak_ptr;

public:

	ProjectView (mojo::project_ptr project);

	~ProjectView ();

private:

	bool on_project_signal_close ();

	void on_project_signal_destroy ();

	bool on_edit_window_delete_event ();

private:

	mojo::project_ptr m_project;

	// per project windows

	gtk::Window::ptr m_edit_window;

};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
