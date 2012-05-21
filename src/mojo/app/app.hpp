
#ifndef MOJO_APP
#define MOJO_APP

#include <mojo/core/typedefs.hpp>
#include <mojo/core/filesystem.hpp>

#include <mojo/typesystem/typedefs.hpp>

#include "typedefs.hpp"

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
	static AppSP init (int argc, char *argv[]);

	static AudioFileSP open_audiofile (const fs::path& p);

	static ModuleSPSet get_modules ();

	static AudioFileModuleSPSet get_audiofile_modules ();

	static AudioDriverModuleSPSet get_audio_driver_modules ();

	static AudioEffectModuleSPSet get_audio_effect_modules ();

	static ArchiveModuleSPSet get_archive_modules ();

	static ArchiveSP create_archive ();

private:

	void register_types ();

private: // member data

	static App*     s_app;

	TypeSystemSP          m_type_system;

	ModuleSPSet               m_modules;

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
