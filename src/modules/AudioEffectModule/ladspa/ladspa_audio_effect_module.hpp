
#ifndef MOJO_LADSPA_AUDIO_EFFECT_MODULE
#define MOJO_LADSPA_AUDIO_EFFECT_MODULE

#include <mojo/mojo.hpp>

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

	virtual AudioEffectSPtr open (AudioEffectInfoSPtr info, samplerate_t rate);

	virtual paths_t get_plugin_directory_paths () const;

	virtual void set_plugin_directory_paths (const paths_t& paths);

	virtual paths_t get_preset_directory_paths () const;

	virtual void set_preset_directory_paths (const paths_t& paths);

	virtual AudioEffectInfoSet get_plugin_info ();

	virtual std::string get_plugin_api_name () const;

private:

	paths_t m_plugin_dirs;

};

} // namespace mojo

#endif
