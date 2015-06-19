
#ifndef MOJO_AMALGAMATED

#include "mojo/core/object/object_collection.hpp"

#include "audio_track.hpp"
#include "midi_track.hpp"
#include "project.hpp"
#endif

namespace mojo {

const char* const Project::s_property_tracks = "tracks";

void Project::get_properties(Properties& props) const
{
	props.set_property(s_property_tracks, m_tracks);
}

void Project::set_properties(const Properties& props)
{
}

AudioTrackSP Project::new_audio_track(const std::string& name)
{
	AudioTrackSP track(new AudioTrack);
	track->set_name(name);
	m_tracks.insert(track);
	return track;
}

MidiTrackSP Project::new_midi_track(const std::string& name)
{
	MidiTrackSP track(new MidiTrack);
	track->set_name(name);
	m_tracks.insert(track);
	return track;
}

void Project::add_track(const TrackSP& track)
{
	m_tracks.insert(track);

	m_track_added(track.get());
}

void Project::remove_track(const TrackSP& track)
{
	m_tracks.erase(m_tracks.find(track));

	m_track_removed(track.get());
}

signals::connection Project::connect_track_added(const TrackAddedFunc& slot)
{
	return m_track_added.connect(slot);
}

signals::connection Project::connect_track_removed(const TrackRemovedFunc& slot)
{
	return m_track_removed.connect(slot);
}

} // namespace mojo
