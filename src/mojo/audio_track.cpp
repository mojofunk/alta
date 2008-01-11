
#include <mojo/audio_track.hpp>

namespace mojo {

AudioTrack::AudioTrack()
{

}

void
AudioTrack::get_property (const std::string& name, boost::any& value) const
{
	return Track::get_property (name, value);
}

void
AudioTrack::set_property (const std::string& name, const boost::any& value)
{
	Track::set_property (name, value);

}

std::vector<std::string>
AudioTrack::get_property_names () const
{
	return Track::get_property_names();
}

} // namespace mojo
