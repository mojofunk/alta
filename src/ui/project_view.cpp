
#include <boost/bind.hpp>

#include <ui/project_view.hpp>

#include <ui/debug/debug.hpp>

namespace gmojo {

ProjectView::ProjectView(mojo::Project* project)
	:
		m_project(project),
		m_edit_window(project)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_project->ref();
    
	// get notification of project "destruction" for unref
	m_project->signal_destroy().connect
		(
		 boost::bind (
			 boost::mem_fn (&ProjectView::on_project_signal_destroy),
			 this)
		);
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

	// I think this should be in edit window
	gtk_main();
}

bool
ProjectView::quit()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// I think this should be in edit window
	gtk_main_quit();
	return true;
}

void
ProjectView::on_project_signal_destroy ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// disconnect signals connected to project
	
	// unref project
	m_project->unref();

	// close all the project windows

	quit ();

	m_signal_destroy ();
}

} // namespace gmojo
