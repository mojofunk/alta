
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

}

void
Project::save_as (const fs::path& directory, const string& name)
{
	const string extension = "mojo";
	m_file_path = directory / (name + extension);

	// move project files to directory etc

	save ();

}

#if 0
void
Project::create_audio_track ()
{

}
#endif

} // namespace mojo
