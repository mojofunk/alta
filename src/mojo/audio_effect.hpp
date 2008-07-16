
#ifndef MOJO_AUDIO_EFFECT_INCLUDED
#define MOJO_AUDIO_EFFECT_INCLUDED

#include <vector>

#include <mojo/object.hpp>
#include <mojo/audio_effect_parameter.hpp>

namespace mojo {

typedef std::vector<AudioEffectParameter*> ParameterList;

class AudioEffect : public Object
{
public: // constructors

	virtual ~AudioEffect ();

public: // Object interface

	virtual void get_properties (Properties& props) const = 0;

	virtual void set_properties (const Properties& props) = 0;

public: // AudioEffect interface

	virtual void get_parameters (ParameterList& params) const = 0;


};

} // namespace mojo

#endif
