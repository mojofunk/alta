
#include <mojo/archive_utils.hpp>
#include <mojo/archive.hpp>

#include <mojo/audio_track.hpp>
#include <mojo/midi_track.hpp>
#include <mojo/object_collection.hpp>

#include <mojo/project.hpp>

namespace mojo {

const char * const Project::s_property_tracks = "tracks";

Project::Project()
{

}

Project::~Project()
{

}

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

void
Project::save () const
{
	ArchiveSPtr archive = create_mojo_archive(); 

	Properties props;
	get_properties(props);

	archive->write (m_file_path.string(), props);
}

void
Project::save_as (const fs::path& directory, const string& name)
{
	const string extension = ".mojo";
	m_file_path = directory / (name + extension);

	// move project files to directory etc

	save ();
}

} // namespace mojo
