
#ifndef MOJO_AUDIO_EFFECT_MODULE
#define MOJO_AUDIO_EFFECT_MODULE

#include <mojo/module.hpp>
#include <mojo/filesystem.hpp>
#include <mojo/typedefs.hpp>

namespace mojo {

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
	virtual AudioEffectSPtr open (const fs::path& path) = 0;

	virtual void get_plugin_paths (paths_t& paths) = 0;

	virtual void set_plugin_paths (const paths_t& paths) = 0;

	virtual void get_preset_paths (paths_t& paths) = 0;

	virtual void set_preset_paths (const paths_t& paths) = 0;

};

} // namespace mojo

#endif
