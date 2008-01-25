
#ifndef MOJO_AUDIO_EFFECT_PLUGIN_INCLUDED
#define MOJO_AUDIO_EFFECT_PLUGIN_INCLUDED

#include <mojo/plugin.hpp>

namespace mojo {

/**
 * The AudioEffectPlugin interface enables support
 * for different plugin AudioEffect API's such as VST, LADSPA,
 * AudioUnit and LV2.
 */
class AudioEffectPlugin : public Plugin
{
public:

	virtual ~AudioEffectPlugin ();

protected:

	AudioEffectPlugin ();

};

}

#endif
