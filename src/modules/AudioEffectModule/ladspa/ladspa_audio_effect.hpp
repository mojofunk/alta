
#ifndef MOJO_LADSPA_AUDIO_EFFECT
#define MOJO_LADSPA_AUDIO_EFFECT

//#include <ladspa.h>

#include <mojo/audio_effect.hpp>

namespace mojo {

class LADSPAAudioEffect : public AudioEffect
{
public: // ctors

	LADSPAAudioEffect (const std::string& path);

	virtual ~LADSPAAudioEffect ();

public: // AudioEffect interface

	virtual void get_parameters (ParameterList& params) const;

};

} // namespace mojo

#endif
