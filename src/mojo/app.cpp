
#include <mojo/app.hpp>

#include <mojo/project.hpp>
#include <mojo/type_system.hpp>
#include <mojo/register_types.hpp>
#include <mojo/filesystem_paths.hpp>
#include <mojo/module_utils.hpp>
#include <mojo/audio_file_module.hpp>
#include <mojo/audio_driver_module.hpp>
#include <mojo/audio_effect_module.hpp>

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
	, m_modules(discover_modules (module_search_path ()))
{
	register_types();
}

App::~App()
{

}

AudioFileSPtr
App::open_audiofile (const fs::path& p)
{
	// get all the AudioFileModule's that are loaded
	
	// for each module try to create an AudioFile instance
	// from the path

	AudioFileModuleSet modules = get_audiofile_modules ();

	for (AudioFileModuleSet::const_iterator i = modules.begin();
			i != modules.end(); ++i)
	{
		AudioFile* af = (*i)->open (p.string());

		if (af) return AudioFileSPtr(af);
	}

	return AudioFileSPtr();
}

ModuleSet
App::get_modules ()
{
	return s_app->m_modules;
}

AudioFileModuleSet
App::get_audiofile_modules ()
{
	AudioFileModuleSet audiofile_modules;

	for (ModuleSet::iterator i = s_app->m_modules.begin();
			i != s_app->m_modules.end(); ++i)
	{
		AudioFileModuleSPtr p = boost::dynamic_pointer_cast<AudioFileModule>(*i);

		if (p) audiofile_modules.insert (p);
	}

	return audiofile_modules;
}

AudioDriverModuleSet
App::get_audio_driver_modules ()
{
	AudioDriverModuleSet audio_driver_modules;

	for (ModuleSet::iterator i = s_app->m_modules.begin();
			i != s_app->m_modules.end(); ++i)
	{
		AudioDriverModuleSPtr p = boost::dynamic_pointer_cast<AudioDriverModule>(*i);

		if (p) audio_driver_modules.insert (p);
	}

	return audio_driver_modules;
}

AudioEffectModuleSet
App::get_audio_effect_modules ()
{
	AudioEffectModuleSet audio_effect_modules;

	for (ModuleSet::iterator i = s_app->m_modules.begin();
			i != s_app->m_modules.end(); ++i)
	{
		AudioEffectModuleSPtr p = boost::dynamic_pointer_cast<AudioEffectModule>(*i);

		if (p) audio_effect_modules.insert (p);
	}

	return audio_effect_modules;
}

} // namespace mojo
