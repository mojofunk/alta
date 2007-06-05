
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
#include <mojo/project_format.hpp>

namespace mojo {

using std::string;

class Project : public Object
{
public:

	typedef boost::shared_ptr<Project>    ptr;
	typedef boost::weak_ptr<Project>      weak_ptr;

	typedef std::list<AudioTrack*>        AudioTrackList;

	typedef boost::signal<bool ()>        close_signal_t;

public:

    Project ();

    ~Project();

public:

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
	void save_as (ProjectFormat::ptr format,
			const fs::path& directory,
			const fs::path& project_name);


	const fs::path&
		project_file () const { return m_project_file; }

	ProjectFormat::ptr
		format () const { return m_format; }

	/**
	 * @return true if project was closed
	 * close will cause the signal_close
	 * to be emitted. If the return value
	 * of the signal is false then the 
	 * destroy method will be executed
	 */
	void close ();
	
public:

	void create_audio_track ();

	const AudioTrackList&
		audio_tracks () const { return m_audio_tracks; }


public:

	// return connection?
	void on_close (const close_signal_t::slot_type& slot)
	{ m_signal_close.connect(slot); }

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

	ProjectFormat::ptr m_format;

private:

	// signals
	boost::signal<void ()> m_signal_name_change;

	boost::signal<bool ()> m_signal_close;

	boost::signal<void (AudioTrack*)> m_signal_new_audio_track;

};

} // namespace mojo

#endif
