
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <string>

#include <boost/signal.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>

#include <libmojo/object.hpp>
#include <libmojo/audio_track.hpp>

namespace mojo {

using std::string;

class Project : public Object
{
public:

	typedef std::list<AudioTrack*> AudioTrackList;

    Project ();

	virtual void destroy () { }

protected:

    ~Project();

	virtual void dispose () { }
	
public:

	const string&
		get_name () const { return m_name; }

	void set_name (const string& name);

	bool save ();
	// bool save_as ();

	/**
	 * @return true if project was closed
	 * close will cause the signal_close
	 * to be emitted. If the return value
	 * of the signal is false then the 
	 * destroy method will be executed
	 */
	void close ();

	void create_audio_track ();

	const AudioTrackList&
		audio_tracks () const { return m_audio_tracks; }


public:
	
	boost::signal<void ()>&
		signal_name_change () { return m_signal_name_change; }

	boost::signal<bool ()>&
		signal_close () { return m_signal_close; }

	boost::signal<void (AudioTrack*)>&
		signal_new_audio_track () { return m_signal_new_audio_track; }

private:

	// serialization
	friend class boost::serialization::access;
	
	template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(m_name);
			ar & BOOST_SERIALIZATION_NVP(m_audio_tracks);
		}

private:

	// member data
	std::string m_name;


	AudioTrackList m_audio_tracks;


	// signals
	boost::signal<void ()> m_signal_name_change;

	boost::signal<bool ()> m_signal_close;

	boost::signal<void (AudioTrack*)> m_signal_new_audio_track;

};

} // namespace mojo

#endif
