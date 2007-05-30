
#ifndef GMOJO_PROJECT_VIEW_INCLUDED
#define GMOJO_PROJECT_VIEW_INCLUDED

#include <boost/noncopyable.hpp>
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
class ProjectView : public mojo::Object, boost::noncopyable
{
public:

    ProjectView(mojo::Project* project);

    ~ProjectView();

	void run();

	/**
	 * @return false if the user cancels.
	 */
	bool quit();

//   mojo::Project& project() { return *m_project; }

	EditWindow& get_edit_window() { return m_edit_window; }

private:

	void on_project_signal_destroy ();

private:

	mojo::Project* m_project;

	// per project windows

	EditWindow m_edit_window;

};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
