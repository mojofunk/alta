
#include <boost/bind.hpp>

#include <mojo/project.hpp>

#include <ui/app.hpp>
#include <ui/project_view.hpp>
#include <ui/edit_window.hpp>

namespace gmojo {

ProjectView::ProjectView(mojo::ProjectSPtr project)
	:
		m_project(project),
		m_edit_window(new EditWindow(project))
{
	m_edit_window->on_delete_event (
		 boost::bind (&ProjectView::on_edit_window_delete_event, this)
		);
}

ProjectView::~ProjectView()
{

}

bool
ProjectView::on_edit_window_delete_event ()
{
	// disconnect signals connected to the EditWindow
	// although it doesn't really matter in this case

	App::close_project (m_project.get());
	
	return true;
}

} // namespace gmojo
