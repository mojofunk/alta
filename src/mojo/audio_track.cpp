
#include <mojo/audio_track.hpp>

namespace mojo {

AudioTrack::AudioTrack()
	:
		m_name("mojo::AudioTrack")
{

}

std::string
AudioTrack::get_name() const
{
	return m_name;
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

AudioTrack::name_change_signal_t&
AudioTrack::signal_name_change()
{
	return m_signal_name_change;
}

} // namespace mojo
