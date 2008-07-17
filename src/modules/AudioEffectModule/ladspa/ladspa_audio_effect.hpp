
#ifndef MOJO_LADSPA_AUDIO_EFFECT
#define MOJO_LADSPA_AUDIO_EFFECT

//#include <ladspa.h>

#include <mojo/audio_effect.hpp>

namespace mojo {

class LADSPAAudioEffect : public AudioEffect
{
public:

	LADSPAAudioEffect ();

	virtual ~LADSPAAudioEffect ();

};

} // namespace mojo

#endif
