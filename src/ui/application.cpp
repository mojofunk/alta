
#include "application.hpp"
#include "project_view.hpp"

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

}

Application::~Application()
{


}

void
Application::run()
{
	new_project();
}

void
Application::quit()
{

}

void
Application::new_project()
{
	// need to pass in implementation of a async signal bus
	// so that the project can send signals to the gtk 
	// main loop
	// try/catch probably
	mojo::project new_project;

	boost::shared_ptr<ProjectView> pview = ProjectView::create(new_project);

	// check the return?
	m_projects.insert(pview);

	pview->run();

	// Create an temporary project
	// and ProjectView

}

void
Application::open_project(const string& path_to_file)
{
    
    
}

} // namespace gmojo
