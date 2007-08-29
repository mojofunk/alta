
#include <mojo/project.hpp>
#include <mojo/audio_track.hpp>
#include <mojo/project_format.hpp>

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

	if(!m_format)
	{
		throw;
	}

	try
	{
		m_format->save_project (*this, m_project_file);
	}
	catch (...)
	{

	}

}

void
Project::save_as (project_format_ptr format,
		const fs::path& directory, const fs::path& name)
{
	m_format = format;

	m_project_file = directory / name; // + format->extension ();

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

void
Project::create_audio_track ()
{
	audio_track_ptr new_track (new AudioTrack());

	m_audio_tracks.push_back (new_track);

	m_signal_new_audio_track (new_track);
}


} // namespace mojo
