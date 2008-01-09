
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
	if (name == "tracks") {
		value = m_tracks;
	}

}

std::vector<std::string>
Project::get_property_names () const
{
	std::vector<std::string> property_names;

	property_names.push_back ("tracks");

	return property_names;
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
	archive->set_property("tracks", m_tracks);

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

bool
Project::add_audio_track (AudioTrackSPtr track)
{
	return m_tracks.insert(track).second;
}

} // namespace mojo
