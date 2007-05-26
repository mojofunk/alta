
#ifndef GMOJO_PROJECT_VIEW_INCLUDED
#define GMOJO_PROJECT_VIEW_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <libmojo/project.hpp>

#include "edit_window.hpp"

namespace gmojo {

/**
   The project view is intended to be the central
   class through which all the different Views of
   the project are created and accessed.

*/
class ProjectView : boost::noncopyable
{
public:

	void run();

	/**
	 * @return false if the user cancels.
	 */
	bool quit();

//   mojo::Project& project() { return *m_project; }

	static boost::shared_ptr<ProjectView> create (boost::shared_ptr<mojo::Project> project);

private:

    ProjectView(boost::shared_ptr<mojo::Project> project);

    ~ProjectView();

	boost::shared_ptr<mojo::Project> m_project;

	// per project windows

	EditWindow m_edit_window;

private:

	struct deleter;
	friend struct deleter;

	/**
	 * So the destructor can be private and thus
	 * preventing delete sp.get()
	 */
	struct deleter
	{
		void operator()(ProjectView* p) { delete p; }
	};

};

} // namespace gmojo

#endif // GMOJO_PROJECT_VIEW_INCLUDED
