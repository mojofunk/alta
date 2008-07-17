
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

template<class T>
std::set<boost::shared_ptr<T> >
get_modules_of_type (const ModuleSet& modules)
{
	typedef boost::shared_ptr<T> module_type;
	typedef std::set<module_type> set_type;

	set_type mods;

	for (ModuleSet::iterator i = modules.begin();
			i != modules.end(); ++i)
	{
		module_type p = boost::dynamic_pointer_cast<T>(*i);
		if (p) mods.insert (p);
	}
	return mods;
}

AudioFileModuleSet
App::get_audiofile_modules ()
{
	return get_modules_of_type<AudioFileModule> (get_modules());
}

AudioDriverModuleSet
App::get_audio_driver_modules ()
{
	return get_modules_of_type<AudioDriverModule> (get_modules());
}

AudioEffectModuleSet
App::get_audio_effect_modules ()
{
	return get_modules_of_type<AudioEffectModule> (get_modules());
}

} // namespace mojo
