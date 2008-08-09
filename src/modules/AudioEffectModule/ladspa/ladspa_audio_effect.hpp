
#ifndef MOJO_LADSPA_AUDIO_EFFECT
#define MOJO_LADSPA_AUDIO_EFFECT

#include <ladspa.h>

#include <mojo/mojo.hpp>

#include "ladspa_typedefs.hpp"

namespace mojo {

class LADSPAAudioEffect : public AudioEffect
{
public: // ctors

	LADSPAAudioEffect (LADSPAAudioEffectInfoSPtr info, samplerate_t);

	virtual ~LADSPAAudioEffect ();

public: // AudioEffect interface

	virtual AudioEffectInfoSPtr get_info () const;

	virtual ParameterList get_parameter_list () const;

	virtual void get_parameter_info (uint32_t param_id, AudioEffectParameterInfo& info) const;

	virtual float get_parameter (uint32_t param_id) const;

	virtual void set_parameter (uint32_t param_id, float value);

	virtual void activate ();

	virtual void deactivate ();

	virtual void set_block_size (uint32_t frames);

private:

	LibrarySPtr m_library;

	const LADSPA_Descriptor* m_descriptor;

	AudioEffectInfoSPtr m_info;

	LADSPA_Handle m_handle;

	ParameterList m_parameters;

};

} // namespace mojo

#endif
