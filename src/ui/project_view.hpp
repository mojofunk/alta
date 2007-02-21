
#ifndef GMOJO_PROJECT_VIEW_INCLUDED
#define GMOJO_PROJECT_VIEW_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <libmojo/project.hpp>

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

	static boost::shared_ptr<ProjectView> create (mojo::project project);

private:

    ProjectView(mojo::project project);

    ~ProjectView();

	mojo::project m_project;

	/**
	 * The canvasview shouldn't need access to anything
	 * in this class.
	 */
	// ProjectCanvas

    // TransportControl m_transport_control;


private:


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
