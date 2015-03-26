#ifndef MOJO_APPLICATION_AMALGAMATED
#include "audio_clip.hpp"
#endif

namespace mojo {

AudioClip::AudioClip(const std::string& audiofile)
    : m_audiofile(audiofile)
{
}

AudioClip::AudioClip() {}

void AudioClip::get_properties(Properties& props) const {}

void AudioClip::set_properties(const Properties& props) {}

} // namespace mojo
