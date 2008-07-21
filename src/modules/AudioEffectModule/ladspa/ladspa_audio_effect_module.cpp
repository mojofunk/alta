
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

AudioEffectSPtr
LADSPAAudioEffectModule::open (const fs::path& path)
{
	return AudioEffectSPtr(new LADSPAAudioEffect (path));
}

paths_t
LADSPAAudioEffectModule::get_plugin_directory_paths () const
{
	return paths_t();
}

void
LADSPAAudioEffectModule::set_plugin_directory_paths (const paths_t& paths)
{

}

paths_t
LADSPAAudioEffectModule::get_preset_directory_paths () const
{
	return paths_t();
}

void
LADSPAAudioEffectModule::set_preset_directory_paths (const paths_t& paths)
{

}

paths_t
LADSPAAudioEffectModule::get_plugin_paths ()
{
	return paths_t();
}

std::string
LADSPAAudioEffectModule::get_plugin_api_name () const
{
	return "LADSPA";
}

MOJO_CAPI void * mojo_module_factory(void)
{
	return new LADSPAAudioEffectModule;
}

} // namespace mojo
