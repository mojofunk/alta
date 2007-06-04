
#include <mojo/audio_track.hpp>

namespace mojo {

AudioTrack::AudioTrack()
	:
		m_name("")
{
#ifdef MOJO_DEBUG_EXTRA
	LOG_MOJO_DEBUG;
#endif

}

void
AudioTrack::set_name(const std::string& new_name)
{
	if (m_name != new_name)
	{
		m_name = new_name;
		m_signal_name_change ();
	}
}

} // namespace mojo
