#include <boost/bind.hpp>

#include <ui/application.hpp>
#include <ui/project_view.hpp>

#include <ui/debug/debug.hpp>

namespace gmojo {

Application* Application::sm_app;

boost::shared_ptr<Application>
Application::create (int argc, char *argv[])
{
	if(sm_app) throw;

	// try/catch?
	boost::shared_ptr<Application> ptr(new Application(argc, argv), Application::deleter());

	sm_app = ptr.get();

	return ptr;
}

Application::Application (int argc, char *argv[])
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif
}

Application::~Application()
{

#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

}

void
Application::run()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	new_project ();

	gtk_main ();
}

void
Application::quit()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_projects.clear();

	gtk_main_quit ();
}

void
Application::new_project()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	mojo::Project::ptr new_project(new mojo::Project());

	ProjectView::ptr pview(new ProjectView (new_project));

	// a reference to the project is not held by this class
	// so if the project is destroyed rely on the projectview's
	// destroy signal
	pview->on_destroy (
		 boost::bind (
			 &Application::on_projectview_signal_destroy, this,
			 ProjectView::weak_ptr(pview)
			 )
		);

	// check the return?
	m_projects.insert(pview);
}

void
Application::on_projectview_signal_destroy (ProjectView::weak_ptr projectview)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	ProjectView::ptr pview(projectview.lock ());
	
	// check
	m_projects.erase(pview);

	if(m_projects.empty ())
	{
		quit();
	}
}

void
Application::open_project(const string& path_to_file)
{
    
    
}


} // namespace gmojo
