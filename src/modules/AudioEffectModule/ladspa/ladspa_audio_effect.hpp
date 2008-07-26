
#ifndef MOJO_LADSPA_AUDIO_EFFECT
#define MOJO_LADSPA_AUDIO_EFFECT

#include <ladspa.h>

#include <mojo/filesystem.hpp>
#include <mojo/audio_effect.hpp>

namespace mojo {

class LADSPAAudioEffect : public AudioEffect
{
public: // ctors

	LADSPAAudioEffect (const fs::path& path, uint32_t index);

	virtual ~LADSPAAudioEffect ();

public: // AudioEffect interface

	virtual std::string get_name () const;

	virtual void get_parameters (AudioEffectParameterSet& params) const;

private:

	LibrarySPtr m_library;

	const LADSPA_Descriptor* m_descriptor;

};

} // namespace mojo

#endif
