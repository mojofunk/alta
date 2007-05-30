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

	new_project();
}

void
Application::quit()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif


}

void
Application::new_project()
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	mojo::Project* new_project = new mojo::Project();

	ProjectView* pview = new ProjectView (new_project);

	new_project->unref();

	pview->signal_destroy().connect
		(
		 boost::bind (
			 boost::mem_fn (&Application::on_projectview_signal_destroy),
			 this, pview)
		);

	// check the return?
	m_projects.insert(pview);
	
	pview->run();
}

void
Application::on_projectview_signal_destroy (ProjectView* projectview)
{
#ifdef GMOJO_DEBUG_EXTRA
	LOG_GMOJO_DEBUG;
#endif

	m_projects.erase(projectview);

	projectview->unref();

}

void
Application::open_project(const string& path_to_file)
{
    
    
}


} // namespace gmojo
