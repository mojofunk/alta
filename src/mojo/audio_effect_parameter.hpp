
#ifndef MOJO_AUDIO_EFFECT_PARAMETER
#define MOJO_AUDIO_EFFECT_PARAMETER

#include <mojo/object.hpp>

namespace mojo {

class AudioEffectParameter : public Object
{
public: // constructors

	virtual ~AudioEffectParameter();

public: // Object interface

	virtual void get_properties (Properties& props) const = 0;

	virtual void set_properties (const Properties& props) = 0;

public: // AudioEffectParameter interface

	virtual void get_value (float& val) const = 0;

	virtual void set_value (float val) const = 0;

};

} // namespace mojo

#endif
