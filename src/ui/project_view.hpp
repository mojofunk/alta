
#ifndef GMOJO_PROJECT_VIEW_INCLUDED
#define GMOJO_PROJECT_VIEW_INCLUDED

#include <boost/shared_ptr.hpp>

#include <libmojo/project.hpp>

#include <ui/edit_window.hpp>

namespace gmojo {

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed. It also 
   manages the top level windows for a project
*/
class ProjectView : public mojo::Object
{
public:

    ProjectView (mojo::Project* project);

	void destroy ();

protected:

    ~ProjectView ();

	virtual void dispose ();

private:

	bool on_project_signal_close ();

	void on_project_signal_destroy ();

	void on_edit_window_signal_destroy ();

	bool on_edit_window_signal_delete_event ();

private:

	mojo::Project* m_project;

	// per project windows

	EditWindow* m_edit_window;

};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
