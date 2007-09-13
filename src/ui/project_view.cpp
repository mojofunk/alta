
#include <boost/bind.hpp>

#include <mojo/project.hpp>

#include <ui/project_view.hpp>
#include <ui/edit_window.hpp>

namespace gmojo {

ProjectView::ProjectView(mojo::project_ptr project)
	:
		m_project(project),
		m_edit_window(new EditWindow(project))
{
	m_project->on_close (
		 boost::bind (&ProjectView::on_project_signal_close, this)
		);

	m_project->on_destroy (
		 boost::bind (&ProjectView::on_project_signal_destroy, this)
		);

	m_edit_window->on_delete_event (
		 boost::bind (&ProjectView::on_edit_window_delete_event, this)
		);
}

ProjectView::~ProjectView()
{

}

bool
ProjectView::on_project_signal_close ()
{
	// ask to save project etc
	
	return true;
}

void
ProjectView::on_project_signal_destroy ()
{
	// disconnect signals connected to projectview
	// although it doesn't really matter in this case

	// The Application could destroy the ProjectView
	// when the project is destroyed.
	//destroy ();

}

bool
ProjectView::on_edit_window_delete_event ()
{
	// disconnect signals connected to the EditWindow
	// although it doesn't really matter in this case

	m_project->close ();
	
	return true;
}

} // namespace gmojo
