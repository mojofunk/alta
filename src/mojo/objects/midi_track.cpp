
#include "midi_track.hpp"

namespace mojo {

MidiTrack::MidiTrack()
{

}

void
MidiTrack::get_properties (Properties& props) const
{
	Track::get_properties (props);

	//props.insert (make_property (s_property_midi_sequence, ObjectSPtr(m_midi_sequence)));
}

void
MidiTrack::set_properties (const Properties& props)
{
	Track::set_properties (props);

	// XXX
}

} // namespace mojo
