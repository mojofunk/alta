
#include "ladspa_audio_effect_module.hpp"
#include "ladspa_audio_effect.hpp"

#include <mojo/export.h>
#include <mojo/module_utils.hpp>

namespace mojo {

LADSPAAudioEffectModule::LADSPAAudioEffectModule ()
{
	m_plugin_dirs.push_back ("/usr/local/lib64/ladspa");
	m_plugin_dirs.push_back ("/usr/local/lib/ladspa");
	m_plugin_dirs.push_back ("/usr/lib64/ladspa");
	m_plugin_dirs.push_back ("/usr/lib/ladspa");
}

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
	return m_plugin_dirs;
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
	return get_module_paths(m_plugin_dirs);
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
