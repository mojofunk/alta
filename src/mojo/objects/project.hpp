
#ifndef MOJO_PROJECT
#define MOJO_PROJECT

#include <string>
#include <set>

#include <mojo/core/filesystem.hpp>

#include <mojo/objects/typedefs.hpp>
#include <mojo/objects/object.hpp>

namespace mojo {

using std::string;
using std::set;

/**
 * The bus names that represent physical inputs and outputs
 * won't change when the project moves between systems with
 * different hardware devices. The names associated with the
 * hardware devices will change but they should be stored with
 * the project so that for the common case where the project
 * being reloaded on the system that it was last 
 * configured/used on all the connections will be automatic.
 *
 * The Project class contains the tracks and other data needed
 * to reconstruct a project. The additional methods to 
 * get/set_properties should be for convenience.
 *
 * The Project class is not tied to any on disk format
 *
 *
 */
class Project : Object
{
public: // typedefs

	typedef set<TrackSPtr> track_container_t;

public: // Object interface

	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public: // convenience methodks

	AudioTrackSPtr new_audio_track (const std::string& name = "");

	MidiTrackSPtr new_midi_track (const std::string& name = "");

	track_container_t get_tracks () const { return m_tracks; }

private: // member data

	std::string                   m_name;
	track_container_t             m_tracks;

private: // property names
	
	static const char* const s_property_tracks;

};

} // namespace mojo

#endif
