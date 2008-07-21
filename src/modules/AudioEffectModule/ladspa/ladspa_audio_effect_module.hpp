
#ifndef MOJO_LADSPA_AUDIO_EFFECT_MODULE
#define MOJO_LADSPA_AUDIO_EFFECT_MODULE

#include <mojo/audio_effect_module.hpp>

namespace mojo {

class LADSPAAudioEffectModule : public AudioEffectModule
{
public: // constructors

	LADSPAAudioEffectModule();

	~LADSPAAudioEffectModule();

public: // Module interface

	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // AudioEffectModule interface

	virtual AudioEffectSPtr open (const fs::path& path);

	virtual void get_plugin_paths (paths_t& paths);

	virtual void set_plugin_paths (const paths_t& paths);

	virtual void get_preset_paths (paths_t& paths);

	virtual void set_preset_paths (const paths_t& paths);

	virtual void get_plugin_api_name (std::string& name);
};

} // namespace mojo

#endif
