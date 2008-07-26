#include "ladspa_audio_effect.hpp"

#include <mojo/library.hpp>

namespace mojo {

LADSPAAudioEffect::LADSPAAudioEffect (const fs::path& path, uint32_t index)
	: m_library(create_library (path))
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

	m_descriptor = ladspa_func(index);
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
