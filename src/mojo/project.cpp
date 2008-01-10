
#include <mojo/archive_utils.hpp>
#include <mojo/archive.hpp>

#include <mojo/audio_track.hpp>
#include <mojo/object_collection.hpp>

#include <mojo/project.hpp>

namespace mojo {

Project::Project()
{

}

Project::~Project()
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

void
Project::save ()
{
	ArchiveSPtr archive = create_mojo_archive(); 

	// add properties to the archive
	archive->set_property("tracks", ObjectCollection(m_tracks));

	archive->write (m_file_path.string());
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
