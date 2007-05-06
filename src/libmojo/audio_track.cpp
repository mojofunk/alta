
#include "audio_track.hpp"

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
	m_name = name;
	return true;
}

const ido::id_t
AudioTrack::get_identifier() const
{
	return m_id;
}

void
AudioTrack::set_identifier(const ido::id_t id)
{
	m_id = id;
}


	//ido::EventList& get_events();
} // namespace mojo
