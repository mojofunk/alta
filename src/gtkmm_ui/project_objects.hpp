
#ifndef UI_PROJECT_OBJECTS
#define UI_PROJECT_OBJECTS

#include <mojo-application.hpp>

#include <boost/shared_ptr.hpp>

#include <sigc++/trackable.h>

namespace ui {

class ProjectWindow;

/**
 * The ProjectObjects class contains all the objects in the UI
 * that are associated with a project instance.
 *
 * not so sure about the name
 */
class ProjectObjects : public sigc::trackable
{
public:

	ProjectObjects (mojo::Project* p);

        mojo::Project const * get_project () const
        { return m_project; }

private:

        mojo::Project const * m_project;

	boost::shared_ptr<ProjectWindow> m_project_window;

	// mixer window

};

} // namespace ui

#endif
