
#include <mojo/archive_utils.hpp>
#include <mojo/archive.hpp>

#include <mojo/audio_track.hpp>

#include <mojo/project.hpp>

namespace mojo {

Project::Project()
{

}

Project::~Project()
{

}
	
void
Project::get_property (const std::string& name, boost::any& value) const
{

}

void
Project::set_property (const std::string& name, const boost::any& value)
{

}

void
Project::save ()
{
	ArchiveSPtr archive = create_mojo_archive(); 

	// add properties to the archive

	archive->write (m_file_path.string());
}

void
Project::save_as (const fs::path& directory, const string& name)
{
	const string extension = "mojo";
	m_file_path = directory / name;

	fs::change_extension(m_file_path, extension);

	// move project files to directory etc

	save ();

}

bool
Project::add_audio_track (AudioTrackSPtr track)
{
	return m_tracks.insert(track).second;
}

} // namespace mojo
