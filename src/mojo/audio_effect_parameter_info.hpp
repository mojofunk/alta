
#ifndef MOJO_AUDIO_EFFECT_PARAMETER_INFO
#define MOJO_AUDIO_EFFECT_PARAMETER_INFO

#include <string>

namespace mojo {

struct AudioEffectParameterInfo
{
	std::string name;
	float min_value;
	float max_value;
	float default_value;	
};

} // namespace mojo

#endif
