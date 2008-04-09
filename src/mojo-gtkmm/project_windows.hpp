
#ifndef UI_PROJECT_WINDOWS
#define UI_PROJECT_WINDOWS

#include <sigc++/trackable.h>

#include "edit_window.hpp"

namespace ui {

class ProjectWindows : public sigc::trackable
{
public:

	ProjectWindows (Project* p);

private:

	EditWindow m_edit_window;

};

} // namespace ui

#endif
