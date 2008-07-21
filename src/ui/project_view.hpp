
#ifndef GMOJO_PROJECT_VIEW
#define GMOJO_PROJECT_VIEW

#include <ui/widget_ptr.hpp>

namespace gmojo {

class Project;

class ProjectView
{
public:

	ProjectView (Project*);

private: // per project windowss
	
	WidgetSPtr m_edit_window;

};

} // namespace gmojo

#endif
