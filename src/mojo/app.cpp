
#include <mojo/app.hpp>

#include <mojo/project.hpp>
#include <mojo/type_system.hpp>
#include <mojo/register_types.hpp>
#include <mojo/filesystem_paths.hpp>
#include <mojo/plugin_utils.hpp>
#include <mojo/audio_file_plugin.hpp>
#include <mojo/audio_driver_plugin.hpp>

namespace mojo {

App* App::s_app;

AppSPtr
App::init (int argc, char *argv[])
{
	if(s_app) throw;

	// try/catch?
	AppSPtr ptr(new App(argc, argv), App::deleter());

	s_app = ptr.get();

	return ptr;
}

App::App (int argc, char *argv[])
	:
	m_type_system(TypeSystem::init ())
	, m_plugins(discover_plugins (plugin_search_path ()))
{
	register_types();
}

App::~App()
{

}

AudioFileSPtr
App::open_audiofile (const fs::path& p)
{
	// get all the AudioFilePlugin's that are loaded
	
	// for each plugin try to create an AudioFile instance
	// from the path

	AudioFilePluginSet plugins = get_audiofile_plugins ();

	for (AudioFilePluginSet::const_iterator i = plugins.begin();
			i != plugins.end(); ++i)
	{
		AudioFile* af = (*i)->open (p.string());

		if (af) return AudioFileSPtr(af);
	}

	return AudioFileSPtr();
}

PluginSet
App::get_plugins ()
{
	return s_app->m_plugins;
}

AudioFilePluginSet
App::get_audiofile_plugins ()
{
	AudioFilePluginSet audiofile_plugins;

	for (PluginSet::iterator i = s_app->m_plugins.begin();
			i != s_app->m_plugins.end(); ++i)
	{
		AudioFilePluginSPtr p = boost::dynamic_pointer_cast<AudioFilePlugin>(*i);

		if (p) audiofile_plugins.insert (p);
	}

	return audiofile_plugins;
}

AudioDriverPluginSet
App::get_audio_driver_plugins ()
{
	AudioDriverPluginSet audio_driver_plugins;

	for (PluginSet::iterator i = s_app->m_plugins.begin();
			i != s_app->m_plugins.end(); ++i)
	{
		AudioDriverPluginSPtr p = boost::dynamic_pointer_cast<AudioDriverPlugin>(*i);

		if (p) audio_driver_plugins.insert (p);
	}

	return audio_driver_plugins;
}

} // namespace mojo
