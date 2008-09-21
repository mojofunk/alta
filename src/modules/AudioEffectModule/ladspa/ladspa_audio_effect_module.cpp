
#include "ladspa_audio_effect_module.hpp"
#include "ladspa_audio_effect.hpp"
#include "ladspa_audio_effect_info.hpp"
#include "ladspa_typedefs.hpp"

#include <mojo/mojo-internal.hpp>

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

AudioEffectSP
LADSPAAudioEffectModule::open (AudioEffectInfoSP info, samplerate_t rate)
{
	LADSPAAudioEffectInfoSP ladspa_info = boost::dynamic_pointer_cast<LADSPAAudioEffectInfo>(info);
	AudioEffectSP aeffect;

	if (!ladspa_info) return aeffect;

	try
	{
		aeffect = AudioEffectSP(new LADSPAAudioEffect (ladspa_info, rate));
	}
	catch (...)
	{
		//  
	}
	return aeffect;
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

void
get_info (const fs::path& path, AudioEffectInfoSPSet& info_set)
{
	LADSPA_Descriptor_Function ladspa_func = NULL;
	
	LibrarySP lib = create_library (path);

	if (!lib) return;
		
	ladspa_func = (LADSPA_Descriptor_Function)lib->resolve("ladspa_descriptor");

	const LADSPA_Descriptor* descriptor = NULL;
	
	for (uint32_t index = 0;
		       	(descriptor = ladspa_func(index));
		       	++index)
	{
		AudioEffectInfoSP info(new LADSPAAudioEffectInfo(path, index));
		if (info)
		{
			info_set.insert (info);
		}
	}
}

AudioEffectInfoSPSet
LADSPAAudioEffectModule::get_plugin_info ()
{
	paths_t paths;
	find_matching_files (m_plugin_dirs, is_library, paths);

	AudioEffectInfoSPSet info_set;

	for (paths_t::const_iterator i = paths.begin ();
			i != paths.end(); ++i)
	{
		get_info (*i, info_set);
	}
	
	return info_set;
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
