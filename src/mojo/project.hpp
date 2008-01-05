
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

	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

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
