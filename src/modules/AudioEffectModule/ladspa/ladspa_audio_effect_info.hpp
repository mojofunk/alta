
#ifndef MOJO_LADSPA_AUDIO_EFFECT_INFO
#define MOJO_LADSPA_AUDIO_EFFECT_INFO

#include "mojo/interfaces/audio_effect_info.hpp"

namespace mojo {

class LADSPAAudioEffectInfo : public AudioEffectInfo
{
public:

	LADSPAAudioEffectInfo (const fs::path&, uint32_t index);

public: // AudioEffectInfo Inferface

	virtual std::string get_name () const;

	virtual fs::path get_path () const;

	uint32_t get_index () const;

private:

	const fs::path m_path;

	std::string m_name;

	const uint32_t m_index;

};

} // namespace mojo

#endif
