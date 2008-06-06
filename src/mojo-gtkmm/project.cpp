
#include "project.hpp"

#include "project_data.hpp"

#include "audio_track.hpp"

#include "log.hpp"

namespace ui {

Project::Project ()
	: m_data (new ProjectData)
{

}

Project::~Project ()
{
	delete m_data;
}

void
Project::save ()
{
	LOG;
}

void
Project::create_audio_track ()
{
	LOG;

	TrackSPtr track (new AudioTrack);

	if (track)
	{
		m_data->tracks.insert (track);
		m_signal_track_added (track.get());
	}
}

void
Project::set_playing (bool play)
{
	if (m_data->playing != play)
	{
		m_data->playing = play;
		m_signal_transport_changed ();
	}
}

bool
Project::get_playing ()
{
	return m_data->playing;
}

void
Project::set_looping (bool loop)
{
	if (m_data->looping != loop)
	{
		m_data->looping = loop;
		m_signal_transport_changed ();
	}
}

bool
Project::get_looping ()
{
	return m_data->looping;
}

} // namespace ui
