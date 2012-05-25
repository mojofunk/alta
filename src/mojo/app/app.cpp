
#include "mojo/typesystem/type_system.hpp"

#include "mojo/interfaces/audio_file_module.hpp"
#include "mojo/interfaces/audio_driver_module.hpp"
#include "mojo/interfaces/audio_effect_module.hpp"
#include "mojo/interfaces/archive.hpp"
#include "mojo/interfaces/archive_module.hpp"

#include "mojo/fs/filesystem_paths.hpp"

#include "app.hpp"
#include "module_utils.hpp"

namespace mojo {

App* App::s_app;

AppSP
App::init (int argc, char *argv[])
{
	if(s_app) throw;

	// try/catch?
	AppSP ptr(new App(argc, argv), App::deleter());

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

AudioFileSP
App::open_audiofile (const fs::path& p)
{
	AudioFileModuleSPSet modules = get_audiofile_modules ();

	for (AudioFileModuleSPSet::const_iterator i = modules.begin();
			i != modules.end(); ++i)
	{
		AudioFileSP af = (*i)->open (p.string());

		if (af) return af;
	}

	return AudioFileSP();
}

ModuleSPSet
App::get_modules ()
{
	return s_app->m_modules;
}

AudioFileModuleSPSet
App::get_audiofile_modules ()
{
	return get_modules_of_type<AudioFileModule> (get_modules());
}

AudioDriverModuleSPSet
App::get_audio_driver_modules ()
{
	return get_modules_of_type<AudioDriverModule> (get_modules());
}

AudioEffectModuleSPSet
App::get_audio_effect_modules ()
{
	return get_modules_of_type<AudioEffectModule> (get_modules());
}

ArchiveModuleSPSet
App::get_archive_modules ()
{
	return get_modules_of_type<ArchiveModule> (get_modules());
}

ArchiveSP
App::create_archive ()
{
	ArchiveModuleSPSet modules = get_archive_modules (); 

	if (!modules.empty())
	{
		ArchiveModuleSP mod = *modules.begin(); 
		return ArchiveSP(mod->create_archive ()); 
	}
	return ArchiveSP();
}

} // namespace mojo
