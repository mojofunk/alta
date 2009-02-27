
#ifndef UI_PROJECT_WINDOWS
#define UI_PROJECT_WINDOWS

#include <sigc++/trackable.h>

#include "edit_window.hpp"

namespace ui {

class ProjectWindows : public sigc::trackable
{
public:

	ProjectWindows (mojo::Project* p);

        mojo::Project* get_project () const
        { return m_project; }

private:

	EditWindow m_edit_window;

        mojo::Project* m_project;
};

} // namespace ui

#endif
