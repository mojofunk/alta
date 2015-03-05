#ifndef MOJO_AUDIO_EFFECT_INFO_H
#define MOJO_AUDIO_EFFECT_INFO_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header.hpp"
#include "mojo/core/filesystem/filesystem.hpp"
#endif

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

#endif // MOJO_AUDIO_EFFECT_INFO_H
