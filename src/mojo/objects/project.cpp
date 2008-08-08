
#include "audio_track.hpp"
#include "midi_track.hpp"
#include "object_collection.hpp"
#include "project.hpp"

namespace mojo {

const char * const Project::s_property_tracks = "tracks";

void
Project::get_properties (Properties& props) const
{
	props.insert (make_property (s_property_tracks, ObjectCollection(m_tracks)));
}

void
Project::set_properties (const Properties& props)
{

}

AudioTrackSPtr
Project::new_audio_track (const std::string& name)
{
	AudioTrackSPtr track(new AudioTrack);
	track->set_name (name);
	m_tracks.insert(track);
	return track;
}

MidiTrackSPtr
Project::new_midi_track (const std::string& name)
{
	MidiTrackSPtr track(new MidiTrack);
	track->set_name (name);
	m_tracks.insert(track);
	return track;
}

} // namespace mojo
