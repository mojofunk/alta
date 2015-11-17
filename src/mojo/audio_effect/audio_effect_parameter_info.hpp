#ifndef MOJO_AUDIO_EFFECT_PARAMETER_INFO_H
#define MOJO_AUDIO_EFFECT_PARAMETER_INFO_H

struct AudioEffectParameterInfo {
	std::string name;
	float min_value;
	float max_value;
	float default_value;
};

#endif // MOJO_AUDIO_EFFECT_PARAMETER_INFO_H
