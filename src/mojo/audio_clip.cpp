
#include <mojo/audio_clip.hpp>

namespace mojo {

AudioClip::AudioClip (const fs::path& audiofile)
	:
		m_audiofile(audiofile)
{

}

AudioClip::AudioClip ()
{

}

void
AudioClip::get_properties (Properties& props) const
{

}

void
AudioClip::set_properties (const Properties& props)
{

}

} // namespace mojo
