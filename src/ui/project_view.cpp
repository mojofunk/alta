
#include <ui/project_view.hpp>

#include <ui/edit_window.hpp>

namespace gmojo {

ProjectView::ProjectView (Project* project)
	:
		m_edit_window(new EditWindow(project))
{

}

}
