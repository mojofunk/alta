
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <string>

#include <libido/project.hpp>

#include <libmojo/audio_track.hpp>

namespace mojo {

using std::string;

class Project : public ido::IProject
{
public:

    Project();

	const string& get_name() const
	{ return m_name; }

	void set_name(const string& name)
	{ m_name = name; }

private:

	string m_name;

public:

	//IProjectDescription& get_description() = 0;



#if 0

	bool add_audio_track(AudioTrack* audio_track);

	typedef std::list<AudioTrack*> AudioTrackList;

	const AudioTrackList& track_list() const
	{ return m_audio_tracks; }
#endif

};

} // namespace mojo

#endif
