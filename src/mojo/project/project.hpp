
#ifndef MOJO_PROJECT
#define MOJO_PROJECT

#include <string>

#include "mojo/core/object.hpp"

#include "typedefs.hpp"

namespace mojo {

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
public: // Object interface

	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

public: // convenience methodks

	AudioTrackSP new_audio_track (const std::string& name = "");

	MidiTrackSP new_midi_track (const std::string& name = "");

	TrackSPSet get_tracks () const { return m_tracks; }

	void add_track (const TrackSP&);

	void remove_track (const TrackSP&);

private: // member data

	std::string                   m_name;
	TrackSPSet                    m_tracks;

private: // property names
	
	static const char* const s_property_tracks;

};

} // namespace mojo

#endif
