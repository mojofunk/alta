#ifndef MOJO_MIDI_TRACK_INCLUDED
#define MOJO_MIDI_TRACK_INCLUDED

#include <mojo/track.hpp>

namespace mojo {

class MidiTrack : public Track
{
public:

	// constructors
	MidiTrack ();

public:

	// Object interface
	virtual void get_properties (Properties& props) const;

	virtual void set_properties (const Properties& props);

};

} // namespace mojo

#endif
