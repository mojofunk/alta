
#include <mojo/midi_track.hpp>

namespace mojo {

MidiTrack::MidiTrack()
{

}

void
MidiTrack::get_property (const std::string& name, boost::any& value) const
{
	return Track::get_property (name, value);
}

void
MidiTrack::set_property (const std::string& name, const boost::any& value)
{
	Track::set_property (name, value);

}

std::vector<std::string>
MidiTrack::get_property_names () const
{
	return Track::get_property_names();
}

} // namespace mojo
