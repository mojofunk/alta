
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>

#include "audio_track.hpp"

namespace mojo {

/**
 */
class Project
{
public:

    /**
	 * This will create temporary project in a temporary
	 * directory until the project is saved.
	 */
    Project();

	/**
	 * not sure if this should be a shallow or deep copy
	 */
	Project(const Project& other);

    ~Project();

public:

	void set_name(const std::string&);

	const std::string& get_name() const;

	bool add_audio_track(AudioTrack* audio_track);

	typedef std::list<AudioTrack*> AudioTrackList;

	const AudioTrackList& track_list() const
	{ return m_audio_tracks; }

private:

	// serialization
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(m_name);
		ar & BOOST_SERIALIZATION_NVP(m_audio_tracks);
	}

protected:
	
	// member data
	std::string m_name;

	AudioTrackList  m_audio_tracks;

};

} // namespace mojo

#endif // MOJO_PROJECT_HPP
