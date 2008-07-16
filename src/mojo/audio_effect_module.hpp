
#ifndef MOJO_AUDIO_EFFECT_MODULE
#define MOJO_AUDIO_EFFECT_MODULE

#include <mojo/module.hpp>

namespace mojo {

/**
 * The AudioEffectModule interface enables support
 * for different plugin AudioEffect API's such as VST, LADSPA,
 * AudioUnit and LV2.
 */
class AudioEffectModule : public Module
{
public:

	virtual ~AudioEffectModule ();

protected:

	AudioEffectModule ();

};

} // namespace mojo

#endif
