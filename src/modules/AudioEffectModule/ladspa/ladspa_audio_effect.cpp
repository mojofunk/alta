#include "ladspa_audio_effect.hpp"
#include "ladspa_audio_effect_info.hpp"

#include <mojo/library.hpp>

namespace mojo {

LADSPAAudioEffect::LADSPAAudioEffect (LADSPAAudioEffectInfoSPtr info)
	: m_library(create_library (info->get_path()))
	, m_descriptor(NULL)
{
	LADSPA_Descriptor_Function ladspa_func = NULL;

	if (m_library)
	{
		ladspa_func = (LADSPA_Descriptor_Function)m_library->resolve("ladspa_descriptor");
	}

	if (ladspa_func == NULL)
	{
		throw;
	}

	m_descriptor = ladspa_func(info->get_index());

	if ((m_descriptor) == NULL)
	{
		throw;
	}
}

LADSPAAudioEffect::~LADSPAAudioEffect() { }

std::string
LADSPAAudioEffect::get_name () const
{
	return m_descriptor->Name;
}

void
LADSPAAudioEffect::get_parameters (AudioEffectParameterSet& params) const
{

}

} // namespace mojo
