
#ifndef MOJO_PROJECT_INCLUDED
#define MOJO_PROJECT_INCLUDED

#include <string>
#include <vector>

#include <mojo/object.hpp>
#include <mojo/audio_track_ptr.hpp>
#include <mojo/filesystem.hpp>

namespace mojo {

using std::string;
using std::vector;

class Project : public Object
{
public:

	// constructors
	Project ();

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
	 * Save the project using the project format
	 * to a specific directory.
	 *
	 * The project format will then be used by
	 * further calls to save ()
	 */
	void save_as (const fs::path& directory,
			const string& file_name);

	const fs::path& file () const { return m_file_path; }

	/**
	 * @return true if project was closed
	 * close will cause the signal_close
	 * to be emitted. If the return value
	 * of the signal is false then the 
	 * destroy method will be executed
	 */
	void close ();

	//void create_audio_track ();

private:

	// member data
	fs::path                      m_file_path;

	std::string                   m_name;

	// this needs to hold any track types
	//TrackList                     m_tracks;

};

} // namespace mojo

#endif
