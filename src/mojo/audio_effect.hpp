
#ifndef MOJO_AUDIO_EFFECT_INCLUDED
#define MOJO_AUDIO_EFFECT_INCLUDED

#include <vector>

#include <mojo/audio_effect_parameter.hpp>

namespace mojo {

typedef std::vector<AudioEffectParameter*> ParameterList;

class AudioEffect
{
public: // constructors

	virtual ~AudioEffect ();

public: // AudioEffect interface

	virtual void get_parameters (ParameterList& params) const = 0;

};

} // namespace mojo

#endif
