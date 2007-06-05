
#include <boost/bind.hpp>

#include <ui/project_view.hpp>

#include <ui/debug/debug.hpp>

namespace gmojo {

ProjectView::ProjectView(mojo::Project::ptr project)
	:
		m_project(project),
		m_edit_window(new EditWindow(project))
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
	
	m_project->signal_close ().connect
		(
		 boost::bind (
			 boost::mem_fn (&ProjectView::on_project_signal_close),
			 this)
		);

	m_project->on_destroy
		(
		 boost::bind (
			 boost::mem_fn (&ProjectView::on_project_signal_destroy),
			 this)
		);

	m_edit_window->on_delete_event
		(
		 boost::bind (
			 boost::mem_fn (&ProjectView::on_edit_window_signal_delete_event),
			 this)
		);
}

ProjectView::~ProjectView()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

bool
ProjectView::on_project_signal_close ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// ask to save project etc
	
	return true;
}

void
ProjectView::on_project_signal_destroy ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// disconnect signals connected to projectview
	// although it doesn't really matter in this case

	// The Application could destroy the ProjectView
	// when the project is destroyed.
	destroy ();

}

bool
ProjectView::on_edit_window_signal_delete_event ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// disconnect signals connected to the EditWindow
	// although it doesn't really matter in this case

	m_project->close ();
	
	return true;
}
} // namespace gmojo
