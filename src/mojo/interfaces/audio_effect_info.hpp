
#ifndef MOJO_AUDIO_EFFECT_INFO
#define MOJO_AUDIO_EFFECT_INFO

#include <string>

#include "mojo/fs/filesystem.hpp"

namespace mojo {

class AudioEffectInfo
{
public: // Constructors

	virtual ~AudioEffectInfo ();

public: // AudioEffectInfo interface

	virtual std::string get_name () const = 0;

	virtual fs::path get_path () const = 0;

};

} // namespace mojo

#endif
