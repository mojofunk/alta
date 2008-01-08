
#include <mojo/audio_track.hpp>

namespace mojo {

AudioTrack::AudioTrack()
	:
		m_name("mojo::AudioTrack")
{

}

void
AudioTrack::get_property (const std::string& name, boost::any& value) const
{

}

void
AudioTrack::set_property (const std::string& name, const boost::any& value)
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
	}
}

} // namespace mojo
