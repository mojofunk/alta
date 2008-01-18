
#include <mojo/application.hpp>

#include <mojo/project.hpp>
#include <mojo/type_system.hpp>
#include <mojo/register_types.hpp>
#include <mojo/filesystem_paths.hpp>
#include <mojo/plugin_utils.hpp>

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
		m_type_system(TypeSystem::init ()),
		m_plugins(discover_plugins (plugin_search_path ()))
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

PluginSet
Application::get_plugins ()
{
	return s_app->m_plugins;
}

} // namespace mojo
