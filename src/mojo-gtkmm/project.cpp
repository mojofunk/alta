
#include "project.hpp"

#include "project_data.hpp"

#include "audio_track.hpp"

#include <iostream>

using namespace std;

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
	cout << "Project::save called" << endl;
}

void
Project::create_audio_track ()
{
	cout << "Project::create_audio_track called" << endl;
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
