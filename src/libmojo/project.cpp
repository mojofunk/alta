
#include "project.hpp"

#include "debug.hpp"

namespace mojo {

Project::Project ()
{
#ifdef MOJO_DEBUG
	LOG_MOJO_DEBUG;
#endif

}

Project::Project(const Project& other)
: m_name(other.m_name)
{

}

Project::~Project()
{


}

void
Project::set_name (const std::string& new_name)
{
	m_name = new_name;
}

const std::string&
Project::get_name () const
{
	return m_name;
}

bool
Project::add_audio_track(AudioTrack* audio_track)
{
	m_audio_tracks.push_back(audio_track);

	return true;
}

} // namespace mojo
