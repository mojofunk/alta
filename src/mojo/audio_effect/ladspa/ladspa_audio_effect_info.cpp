#include <ladspa.h>

#include "mojo-audio-effect.hpp"

#include "ladspa_audio_effect_info.hpp"

namespace mojo {

LADSPAAudioEffectInfo::LADSPAAudioEffectInfo(const fs::path& path,
                                             uint32_t index)
    : m_path(path)
    , m_index(index)
{
	LADSPA_Descriptor_Function ladspa_func = NULL;

	LibrarySP lib = create_library(path);

	const LADSPA_Descriptor* descriptor = NULL;

	if (!lib) {
		throw;
	}

	ladspa_func = (LADSPA_Descriptor_Function)lib->resolve("ladspa_descriptor");

	if (ladspa_func == NULL) {
		throw;
	}

	descriptor = ladspa_func(index);

	if (!descriptor) {
		throw;
	}

	m_name = descriptor->Name;
}

std::string LADSPAAudioEffectInfo::get_name() const { return m_name; }

fs::path LADSPAAudioEffectInfo::get_path() const { return m_path; }

uint32_t LADSPAAudioEffectInfo::get_index() const { return m_index; }

} // namespace mojo
