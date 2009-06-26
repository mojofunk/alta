
#ifndef UI_PROJECT_OBJECTS
#define UI_PROJECT_OBJECTS

#include <sigc++/trackable.h>

#include "project_window.hpp"

namespace ui {

/**
 * The ProjectObjects class contains all the objects in the UI
 * that are associated with a project instance.
 */
class ProjectObjects : public sigc::trackable
{
public:

	ProjectObjects (mojo::Project* p);

        mojo::Project const * get_project () const
        { return m_project; }

private:

        mojo::Project const * m_project;

	ProjectWindow m_project_window;

};

} // namespace ui

#endif
