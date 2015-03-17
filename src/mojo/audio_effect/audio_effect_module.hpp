#ifndef MOJO_AUDIO_EFFECT_MODULE_H
#define MOJO_AUDIO_EFFECT_MODULE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/typesystem/types.hpp"
#include "mojo/core/filesystem/filesystem.hpp"
#include "mojo/core/modules/module.hpp"
#include "mojo/audio_effect/typedefs.hpp"
#endif

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

	virtual AudioEffectSP open (AudioEffectInfoSP, samplerate_t) = 0;

	virtual paths_t get_plugin_directory_paths () const = 0;

	virtual void set_plugin_directory_paths (const paths_t& paths) = 0;

	virtual paths_t get_preset_directory_paths () const = 0;

	virtual void set_preset_directory_paths (const paths_t& paths) = 0;

	virtual AudioEffectInfoSPSet get_plugin_info () = 0;

	virtual std::string get_plugin_api_name () const = 0;
};

} // namespace mojo

#endif // MOJO_AUDIO_EFFECT_MODULE_H