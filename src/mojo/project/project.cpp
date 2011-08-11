
#include "audio_track.hpp"
#include "midi_track.hpp"
#include "object_collection.hpp"
#include "project.hpp"

namespace mojo {

const char * const Project::s_property_tracks = "tracks";

void
Project::get_properties (Properties& props) const
{
	props.insert (make_property (s_property_tracks, m_tracks));
}

void
Project::set_properties (const Properties& props)
{

}

AudioTrackSP
Project::new_audio_track (const std::string& name)
{
	AudioTrackSP track(new AudioTrack);
	track->set_name (name);
	m_tracks.insert(track);
	return track;
}

MidiTrackSP
Project::new_midi_track (const std::string& name)
{
	MidiTrackSP track(new MidiTrack);
	track->set_name (name);
	m_tracks.insert(track);
	return track;
}

void
Project::add_track (const TrackSP& track)
{
	m_tracks.insert(track);
}

void
Project::remove_track (const TrackSP& track)
{
	m_tracks.erase(m_tracks.find(track));
}

} // namespace mojo
