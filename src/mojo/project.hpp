
#ifndef MOJO_PROJECT_HPP
#define MOJO_PROJECT_HPP

#include <string>

#include <boost/signal.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>

#include <booty/filesystem.hpp>

#include <mojo/object.hpp>
#include <mojo/audio_track.hpp>

namespace mojo {

using std::string;

class ProjectFormat;

class Project : public Object
{
public:

	typedef std::list<AudioTrack*> AudioTrackList;

    Project ();

	virtual void destroy ()
	{ m_signal_destroy (); }

	/**
	 * This will save the file using the current
	 * name + ProjectFormat::extension using the
	 * current ProjectFormat. If there is no
	 * ProjectFormat then an exception will be 
	 * thrown or some indication of error.
	 */
	void save ();

	/**
	 * Save the project using the project format
	 * to a specific directory.
	 *
	 * The project format will then be used by
	 * further calls to save ()
	 */
	void save_as (ProjectFormat* format,
			const fs::path& directory,
			const fs::path& project_name);


	const fs::path&
		project_file () const { return m_project_file; }

	ProjectFormat*
		format () const { return m_format; }

	/**
	 * @return true if project was closed
	 * close will cause the signal_close
	 * to be emitted. If the return value
	 * of the signal is false then the 
	 * destroy method will be executed
	 */
	void close ();


protected:

    ~Project();

	virtual void dispose ();
	
public:

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
			ar & BOOST_SERIALIZATION_NVP(m_audio_tracks);
		}

private:

	// member data
	fs::path m_project_file;

	AudioTrackList m_audio_tracks;

	ProjectFormat* m_format;

private:

	// signals
	boost::signal<void ()> m_signal_name_change;

	boost::signal<bool ()> m_signal_close;

	boost::signal<void (AudioTrack*)> m_signal_new_audio_track;

};

} // namespace mojo

#endif
