
#ifndef LIBIDO_PROJECT_HPP
#define LIBIDO_PROJECT_HPP

#include <libido/audio_track.hpp>

namespace ido {

/**
 * A project collects together a set of files and folders.
 *
 * A project's location controls where the project's resources are 
 * stored in the local file system.
 *
 * A project can carry session and persistent properties?
 */
class IProject
{
public:

    virtual ~IProject() { }

public:

#if 0

	bool add_audio_track(AudioTrack* audio_track);

	typedef std::list<AudioTrack*> AudioTrackList;

	const AudioTrackList& track_list() const
	{ return m_audio_tracks; }
#endif

};

} // namespace ido

#endif
