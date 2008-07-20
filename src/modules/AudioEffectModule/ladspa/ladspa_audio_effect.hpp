
#ifndef MOJO_LADSPA_AUDIO_EFFECT
#define MOJO_LADSPA_AUDIO_EFFECT

//#include <ladspa.h>

#include <mojo/filesystem.hpp>
#include <mojo/audio_effect.hpp>

namespace mojo {

class LADSPAAudioEffect : public AudioEffect
{
public: // ctors

	LADSPAAudioEffect (const fs::path& path);

	virtual ~LADSPAAudioEffect ();

public: // AudioEffect interface

	virtual void get_parameters (AudioEffectParameterSet& params) const;

};

} // namespace mojo

#endif
