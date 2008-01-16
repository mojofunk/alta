
#include <mojo/application.hpp>

#include <mojo/project.hpp>
#include <mojo/type_system.hpp>
#include <mojo/register_types.hpp>

namespace mojo {

Application* Application::s_app;

ApplicationSPtr
Application::init (int argc, char *argv[])
{
	if(s_app) throw;

	// try/catch?
	ApplicationSPtr ptr(new Application(argc, argv), Application::deleter());

	s_app = ptr.get();

	return ptr;
}

Application::Application (int argc, char *argv[])
	:
		m_type_system(TypeSystem::init())
{
	register_types();
}

Application::~Application()
{

}

AudioFileSPtr
Application::open_audiofile (const fs::path& p)
{
	// get all the AudioFilePlugin's that are loaded
	
	// for each plugin try to create an AudioFile instance
	// from the path
	return AudioFileSPtr();
}

} // namespace mojo
