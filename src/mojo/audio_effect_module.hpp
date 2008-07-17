
#ifndef MOJO_AUDIO_EFFECT_MODULE
#define MOJO_AUDIO_EFFECT_MODULE

#include <mojo/module.hpp>

namespace mojo {

class AudioEffect;

/**
 * The AudioEffectModule interface enables support
 * for different plugin AudioEffect API's such as VST, LADSPA,
 * AudioUnit and LV2.
 */
class AudioEffectModule : public Module
{
public: // ctors

	virtual ~AudioEffectModule ();

protected:

	AudioEffectModule ();

public: // Interface

	/**
	 * return new AudioEffect or 0 on failure
	 */
	virtual AudioEffect* open (const std::string& path) = 0;

	virtual void close (AudioEffect* ae) = 0; 
};

} // namespace mojo

#endif
