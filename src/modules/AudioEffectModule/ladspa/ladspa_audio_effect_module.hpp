
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

};

} // namespace mojo

#endif
