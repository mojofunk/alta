
#include <mojo/app.hpp>

#include <mojo/typesystem/type_system.hpp>

#include <mojo/project.hpp>
#include <mojo/register_types.hpp>
#include <mojo/filesystem_paths.hpp>
#include <mojo/module_utils.hpp>
#include <mojo/audio_file_module.hpp>
#include <mojo/audio_driver_module.hpp>
#include <mojo/audio_effect_module.hpp>
#include <mojo/archive.hpp>
#include <mojo/archive_module.hpp>

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
	AudioFileModuleSet modules = get_audiofile_modules ();

	for (AudioFileModuleSet::const_iterator i = modules.begin();
			i != modules.end(); ++i)
	{
		AudioFileSPtr af = (*i)->open (p.string());

		if (af) return af;
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

ArchiveModuleSet
App::get_archive_modules ()
{
	return get_modules_of_type<ArchiveModule> (get_modules());
}

ArchiveSPtr
App::create_archive ()
{
	ArchiveModuleSet modules = get_archive_modules (); 

	if (!modules.empty())
	{
		ArchiveModuleSPtr mod = *modules.begin(); 
		return ArchiveSPtr(mod->create_archive ()); 
	}
	return ArchiveSPtr();
}

} // namespace mojo
