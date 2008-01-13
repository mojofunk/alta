
#ifndef MOJO_PROJECT_INCLUDED
#define MOJO_PROJECT_INCLUDED

#include <string>
#include <set>

#include <mojo/object.hpp>
#include <mojo/track_ptr.hpp>
#include <mojo/audio_track_ptr.hpp>
#include <mojo/midi_track_ptr.hpp>

#include <mojo/filesystem.hpp>

namespace mojo {

using std::string;
using std::set;

class Project : Object
{
public:

	typedef set<TrackSPtr> track_container_t;

public:

	// new project constructor
	Project();

	// existing project constructor
	Project(const fs::path& project_file);

	~Project();

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public:

	AudioTrackSPtr new_audio_track (const std::string& name = "");

	MidiTrackSPtr new_midi_track (const std::string& name = "");

	// methods
	/**
	 * This will save the file using the current
	 * name + ProjectFormat::extension using the
	 * current ProjectFormat. If there is no
	 * ProjectFormat then an exception will be 
	 * thrown or some indication of error.
	 */
	void save () const;

	/**
	 * Save the project to the specified directory
	 */
	void save_as (const fs::path& directory,
			const string& file_name);

	const fs::path& file () const { return m_file_path; }

	track_container_t get_tracks () const { return m_tracks; }

private:

	// member data
	fs::path                      m_file_path;

	std::string                   m_name;

	// this needs to hold any track types
	track_container_t             m_tracks;

private:
	
	static const char* const s_property_tracks;

};

} // namespace mojo

#endif
