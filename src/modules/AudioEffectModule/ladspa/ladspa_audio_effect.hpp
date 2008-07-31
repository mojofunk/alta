
#ifndef MOJO_LADSPA_AUDIO_EFFECT
#define MOJO_LADSPA_AUDIO_EFFECT

#include <ladspa.h>

#include <mojo/filesystem.hpp>
#include <mojo/audio_effect.hpp>

#include "ladspa_typedefs.hpp"

namespace mojo {

class LADSPAAudioEffect : public AudioEffect
{
public: // ctors

	LADSPAAudioEffect (LADSPAAudioEffectInfoSPtr info);

	virtual ~LADSPAAudioEffect ();

public: // AudioEffect interface

	virtual AudioEffectInfoSPtr get_info () const;

	virtual void get_parameters (AudioEffectParameterSet& params) const;

private:

	LibrarySPtr m_library;

	const LADSPA_Descriptor* m_descriptor;

	AudioEffectInfoSPtr m_info;

};

} // namespace mojo

#endif
