
#ifndef MOJO_PROJECT_INCLUDED
#define MOJO_PROJECT_INCLUDED

#include <string>
#include <set>

#include <mojo/audio_track_ptr.hpp>
#include <mojo/filesystem.hpp>

namespace mojo {

using std::string;
using std::set;

class Project
{
public:
	typedef set<AudioTrackSPtr> TrackList;

public:

	// new project constructor
	Project();

	// existing project constructor
	Project(const fs::path& project_file);

	~Project();

public:

	// methods
	/**
	 * This will save the file using the current
	 * name + ProjectFormat::extension using the
	 * current ProjectFormat. If there is no
	 * ProjectFormat then an exception will be 
	 * thrown or some indication of error.
	 */
	void save ();

	/**
	 * Save the project to the specified directory
	 */
	void save_as (const fs::path& directory,
			const string& file_name);

	const fs::path& file () const { return m_file_path; }

	bool add_audio_track (AudioTrackSPtr audio_track);

	//void create_audio_track ();

private:

	// member data
	fs::path                      m_file_path;

	std::string                   m_name;

	// this needs to hold any track types
	TrackList                     m_tracks;

};

} // namespace mojo

#endif
