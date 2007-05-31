
#include <boost/bind.hpp>

#include <ui/project_view.hpp>

#include <ui/debug/debug.hpp>

namespace gmojo {

ProjectView::ProjectView(mojo::Project* project)
	:
		m_project(project),
		m_edit_window(new EditWindow(project))
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_project->ref ();
	
	m_project->signal_close ().connect
		(
		 boost::bind (
			 boost::mem_fn (&ProjectView::on_project_signal_close),
			 this)
		);

	m_project->signal_destroy ().connect
		(
		 boost::bind (
			 boost::mem_fn (&ProjectView::on_project_signal_destroy),
			 this)
		);

	m_edit_window->signal_destroy ().connect
		(
		 boost::bind (
			 boost::mem_fn (&ProjectView::on_edit_window_signal_destroy),
			 this)
		);
	
	m_edit_window->signal_delete_event ().connect
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

void
ProjectView::destroy ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_edit_window->destroy ();

	m_signal_destroy ();
}

void
ProjectView::dispose ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	if (m_project) m_project->unref ();

	if (m_edit_window) m_edit_window->unref ();
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

	m_project->unref ();
	m_project = 0;

	// The Application could destroy the ProjectView
	// when the project is destroyed.
	destroy ();

}

void
ProjectView::on_edit_window_signal_destroy ()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	// disconnect signals connected to the EditWindow
	// although it doesn't really matter in this case

	m_edit_window->unref ();

	m_edit_window = 0;
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
