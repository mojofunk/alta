
#ifndef MOJO_LADSPA_AUDIO_EFFECT
#define MOJO_LADSPA_AUDIO_EFFECT

#include <ladspa.h>

#include <mojo/filesystem.hpp>
#include <mojo/audio_effect.hpp>
#include <mojo/types.hpp>

#include "ladspa_typedefs.hpp"

namespace mojo {

class LADSPAAudioEffect : public AudioEffect
{
public: // ctors

	LADSPAAudioEffect (LADSPAAudioEffectInfoSPtr info, samplerate_t);

	virtual ~LADSPAAudioEffect ();

public: // AudioEffect interface

	virtual AudioEffectInfoSPtr get_info () const;

	virtual void get_parameters (AudioEffectParameterSet& params) const;

private:

	LibrarySPtr m_library;

	const LADSPA_Descriptor* m_descriptor;

	AudioEffectInfoSPtr m_info;

	LADSPA_Handle m_handle;

};

} // namespace mojo

#endif
