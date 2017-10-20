#ifndef MOJO_AUDIO_EFFECT_INFO_H
#define MOJO_AUDIO_EFFECT_INFO_H

class AudioEffectInfo
{
public: // Constructors
	virtual ~AudioEffectInfo();

public: // AudioEffectInfo interface
	virtual std::string get_name() const = 0;

	virtual fs::path get_path() const = 0;
};

#endif // MOJO_AUDIO_EFFECT_INFO_H
