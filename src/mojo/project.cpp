
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
Project::get_properties (ark::Properties& props) const
{
	props.insert (ark::Property ("name", m_name));

}

void
Project::set_properties (const ark::Properties& props)
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
	bool close = m_signal_close ();

	if(close)
	{
		destroy ();
	}
}

#if 0
void
Project::create_audio_track ()
{

}
#endif

} // namespace mojo
