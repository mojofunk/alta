#include "project_view.hpp"

namespace gmojo {

ProjectView::ProjectView(mojo::Project* project)
	: m_project(project),
	  m_editor(*this)
{
	m_visible = true;

    // connect

}

void
ProjectView::set_visible(bool yn)
{
    m_visible = yn;
    

    m_visibility_changed();
}

} // namespace gmojo
