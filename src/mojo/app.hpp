
#ifndef MOJO_APP
#define MOJO_APP

#include <mojo/filesystem.hpp>
#include <mojo/typedefs.hpp>

#include <mojo/typesystem/typedefs.hpp>

namespace mojo {

/**
 * I'm not sure what this class should be called but it
 * is intended to hold all the resources that are unique
 * to each process and as such is a singleton. Things like
 * the audio drivers, module management and preferences etc.
 */
class App
{
public: // methods

	// singleton constructor
	static AppSPtr init (int argc, char *argv[]);

	static AudioFileSPtr open_audiofile (const fs::path& p);

	static ModuleSet get_modules ();

	static AudioFileModuleSet get_audiofile_modules ();

	static AudioDriverModuleSet get_audio_driver_modules ();

	static AudioEffectModuleSet get_audio_effect_modules ();

	static ArchiveModuleSet get_archive_modules ();

	static ArchiveSPtr create_archive ();

private: // member data

	static App*     s_app;

	TypeSystemSPtr          m_type_system;

	ModuleSet               m_modules;

private: // constructors
	
	App (int argc, char *argv[]);
	~App();

private: // private deleter for shared_ptr

	struct deleter;
	friend struct deleter;

	struct deleter
	{
		void operator()(App* app)
		{ delete app; s_app = 0; }
	};

};

} // namespace mojo

#endif
