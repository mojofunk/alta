
#include <ui/project_view.hpp>

#include <ui/debug/debug.hpp>

namespace gmojo {

boost::shared_ptr<ProjectView>
ProjectView::create (boost::shared_ptr<mojo::Project> project)
{
	boost::shared_ptr<ProjectView> ptr(new ProjectView(project), ProjectView::deleter());
	return ptr;
}

ProjectView::ProjectView(boost::shared_ptr<mojo::Project> project)
	:
		m_project(project),
		m_edit_window(project)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
    // connect

}

ProjectView::~ProjectView()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
}

void
ProjectView::run()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	
	gtk_main();
}

bool
ProjectView::quit()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	return true;
}

} // namespace gmojo
