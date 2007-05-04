
#include "audio_track.hpp"

#include "debug.hpp"

namespace mojo {

AudioTrack::AudioTrack()
	:
		m_name("")
{
#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG;
#endif

}

const std::string&
AudioTrack::get_name() const
{
	return m_name;
}

bool
AudioTrack::set_name(const std::string& name)
{
#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG << name;
#endif

	m_name = name;
	return true;
}

}
