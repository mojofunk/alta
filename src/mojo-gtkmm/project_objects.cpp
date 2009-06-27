
#include "project_objects.hpp"

#include "project_window.hpp"

namespace ui {

ProjectObjects::ProjectObjects (mojo::Project* proj)
	: m_project(proj)
	, m_project_window(new ProjectWindow(proj))
{


}

} // namespace ui
