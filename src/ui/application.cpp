
#include "application.hpp"
#include "project_view.hpp"

#include "debug.hpp"

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
	// need to pass in implementation of a async signal bus
	// so that the project can send signals to the gtk 
	// main loop
	// try/catch probably
	boost::shared_ptr<mojo::Project> new_project(new mojo::Project);

	boost::shared_ptr<ProjectView> pview = ProjectView::create(new_project);

	// check the return?
	m_projects.insert(pview);

	pview->run();

	// Create an temporary project
	// and ProjectView

}

bool
Application::close_project(boost::shared_ptr<ProjectView> project_view)
{
	return true;

}

void
Application::open_project(const string& path_to_file)
{
    
    
}

} // namespace gmojo
