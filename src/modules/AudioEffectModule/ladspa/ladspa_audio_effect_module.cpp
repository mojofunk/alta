
#include "ladspa_audio_effect_module.hpp"
#include "ladspa_audio_effect.hpp"

#include <mojo/export.h>

namespace mojo {

LADSPAAudioEffectModule::LADSPAAudioEffectModule () { }

LADSPAAudioEffectModule::~LADSPAAudioEffectModule () { }

std::string
LADSPAAudioEffectModule::get_author()
{
	return "Tim Mayberry";
}

std::string
LADSPAAudioEffectModule::get_description()
{
	return "LADSPA module";
}

std::string
LADSPAAudioEffectModule::get_version()
{
	return "0.0.1";
}

AudioEffect*
LADSPAAudioEffectModule::open (const std::string& path)
{
	return new LADSPAAudioEffect (path);
}

void
LADSPAAudioEffectModule::close (AudioEffect* ae)
{
	delete ae;
}

MOJO_CAPI void * mojo_module_factory(void)
{
	return new LADSPAAudioEffectModule;
}

} // namespace mojo
