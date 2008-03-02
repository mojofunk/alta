
#ifndef GMOJO_PROJECT_INCLUDED
#define GMOJO_PROJECT_INCLUDED

#include <boost/shared_ptr.hpp>

#include <mojo/project_ptr.hpp>

#include <ui/gtk/window_ptr.hpp>

namespace gmojo {

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed. It also 
   manages the top level windows for a project
*/
class Project
{
public:

	Project (mojo::ProjectSPtr project);

	~Project ();

	mojo::ProjectSPtr get_project () { return m_project; }

private:

	bool on_edit_window_delete_event ();

private:

	mojo::ProjectSPtr m_project;

	// per project windows

	gtk::WindowSPtr m_edit_window;

};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
