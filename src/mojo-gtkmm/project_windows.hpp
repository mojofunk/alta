
#ifndef UI_PROJECT_WINDOWS
#define UI_PROJECT_WINDOWS

#include <sigc++/trackable.h>

#include "project_window.hpp"

namespace ui {

class ProjectWindows : public sigc::trackable
{
public:

	ProjectWindows (mojo::Project* p);

        mojo::Project const * get_project () const
        { return m_project; }

private:

        mojo::Project const * m_project;

	ProjectWindow m_project_window;

};

} // namespace ui

#endif
