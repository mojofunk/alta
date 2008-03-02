
#ifndef MOJO_APP_INCLUDED
#define MOJO_APP_INCLUDED

#include <boost/shared_ptr.hpp>

#include <mojo/type_system_ptr.hpp>
#include <mojo/audio_file_ptr.hpp>
#include <mojo/filesystem.hpp>
#include <mojo/plugin_set.hpp>
#include <mojo/audio_file_plugin_set.hpp>
#include <mojo/audio_driver_plugin_set.hpp>

namespace mojo {

class App;

typedef boost::shared_ptr<App>    AppSPtr;
typedef boost::weak_ptr<App>      AppWPtr;

/**
 * I'm not sure what this class should be called but it
 * is intended to hold all the resources that are unique
 * to each process and as such is a singleton. Things like
 * the audio drivers, plugin management and preferences etc.
 */
class App
{
public: // methods

	// singleton constructor
	static AppSPtr init (int argc, char *argv[]);

	static AudioFileSPtr open_audiofile (const fs::path& p);

	static PluginSet get_plugins ();

	static AudioFilePluginSet get_audiofile_plugins ();

	static AudioDriverPluginSet get_audio_driver_plugins ();

private: // member data

	static App*     s_app;

	TypeSystemSPtr          m_type_system;

	PluginSet               m_plugins;

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