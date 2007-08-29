
#include <mojo/application.hpp>

#include <mojo/project.hpp>

namespace mojo {

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
Application::set_active_project (project_ptr proj)
{

}

} // namespace mojo
