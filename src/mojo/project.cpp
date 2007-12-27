
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

void
Project::close ()
{

}

#if 0
void
Project::create_audio_track ()
{

}
#endif

} // namespace mojo
