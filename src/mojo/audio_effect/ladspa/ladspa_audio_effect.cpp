#include "ladspa_audio_effect.hpp"
#include "ladspa_audio_effect_info.hpp"

namespace mojo {

LADSPAAudioEffect::LADSPAAudioEffect(LADSPAAudioEffectInfoSP info,
                                     samplerate_t rate)
    : m_library(create_library(info->get_path()))
    , m_descriptor(NULL)
    , m_info(info)
    , m_handle(NULL)
{
	LADSPA_Descriptor_Function ladspa_func = NULL;

	if (m_library) {
		ladspa_func =
		    (LADSPA_Descriptor_Function)m_library->resolve("ladspa_descriptor");
	}

	if (ladspa_func == NULL) {
		throw;
	}

	m_descriptor = ladspa_func(info->get_index());

	if ((m_descriptor) == NULL) {
		throw;
	}

	if (m_descriptor->instantiate == NULL) {
		throw;
	}

	if ((m_handle = m_descriptor->instantiate(m_descriptor, rate)) == NULL) {
		throw;
	}

	for (int i = 0; i != m_descriptor->PortCount; ++i) {
		if (LADSPA_IS_PORT_CONTROL(m_descriptor->PortDescriptors[i])) {
			m_parameters.insert(i);
		}
	}
}

LADSPAAudioEffect::~LADSPAAudioEffect() {}

AudioEffectInfoSP LADSPAAudioEffect::get_info() const { return m_info; }

AudioEffect::ParameterList LADSPAAudioEffect::get_parameter_list() const
{
	return m_parameters;
}

void LADSPAAudioEffect::get_parameter_info(uint32_t param_id,
                                           AudioEffectParameterInfo& info) const
{
	info.name = m_descriptor->PortNames[param_id];
}

float LADSPAAudioEffect::get_parameter(uint32_t param_id) const { return 0; }

void LADSPAAudioEffect::set_parameter(uint32_t param_id, float value) {}

void LADSPAAudioEffect::activate() {}

void LADSPAAudioEffect::deactivate() {}

void LADSPAAudioEffect::set_block_size(uint32_t frames) {}

} // namespace mojo
