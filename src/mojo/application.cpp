
#include <mojo/application.hpp>

#include <mojo/project.hpp>
#include <mojo/type_system.hpp>
#include <mojo/register_types.hpp>

namespace mojo {

Application* Application::sm_app;

ApplicationSPtr
Application::create (int argc, char *argv[])
{
	if(sm_app) throw;

	// try/catch?
	ApplicationSPtr ptr(new Application(argc, argv), Application::deleter());

	sm_app = ptr.get();

	return ptr;
}

Application::Application (int argc, char *argv[])
	:
		m_type_system(TypeSystem::create())
{
	register_types();
}

Application::~Application()
{

}

} // namespace mojo
