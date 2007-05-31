
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <string>

#include <boost/signal.hpp>

#include <libido/project.hpp>

#include <libmojo/object.hpp>
#include <libmojo/audio_track.hpp>

namespace mojo {

using std::string;

class Project : public Object
{
public:

    Project ();

	virtual void destroy () { }

protected:

    ~Project();

	virtual void dispose () { }
	
public:

	const string& get_name () const
	{ return m_name; }

	void set_name (const string& name)
	{ m_name = name; }

	/**
	 * @return true if project was closed
	 * close will cause the signal_close
	 * to be emitted. If the return value
	 * of the signal is false then the 
	 * destroy method will be executed
	 */
	void close ();

	boost::signal<bool ()>& signal_close()
	{ return m_signal_close; }

private:

	string m_name;
	
	// signals

	boost::signal<bool ()> m_signal_close;

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
