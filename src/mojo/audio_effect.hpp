
#ifndef MOJO_AUDIO_EFFECT
#define MOJO_AUDIO_EFFECT

#include <mojo/typedefs.hpp>

namespace mojo {

class AudioEffect
{
public: // constructors

	virtual ~AudioEffect ();

public: // AudioEffect interface

	virtual std::string get_name () const = 0;

	virtual void get_parameters (AudioEffectParameterSet& params) const = 0;

};

} // namespace mojo

#endif
