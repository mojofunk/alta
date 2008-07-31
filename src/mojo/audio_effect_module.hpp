
#ifndef MOJO_AUDIO_EFFECT_MODULE
#define MOJO_AUDIO_EFFECT_MODULE

#include <mojo/module.hpp>
#include <mojo/filesystem.hpp>
#include <mojo/typedefs.hpp>
#include <mojo/types.hpp>

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

	virtual AudioEffectSPtr open (AudioEffectInfoSPtr, samplerate_t) = 0;

	virtual paths_t get_plugin_directory_paths () const = 0;

	virtual void set_plugin_directory_paths (const paths_t& paths) = 0;

	virtual paths_t get_preset_directory_paths () const = 0;

	virtual void set_preset_directory_paths (const paths_t& paths) = 0;

	virtual AudioEffectInfoSet get_plugin_info () = 0;

	virtual std::string get_plugin_api_name () const = 0;
};

} // namespace mojo

#endif
