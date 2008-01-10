
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
	if (name == "name")
	{
		value = m_name;
	}

}

void
AudioTrack::set_property (const std::string& name, const boost::any& value)
{

}

std::vector<std::string>
AudioTrack::get_property_names () const
{
	std::vector<std::string> property_names;

	property_names.push_back ("name");

	return property_names;
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
