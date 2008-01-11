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

	virtual void get_property (const std::string& name,
			boost::any& value) const;

	virtual std::vector<std::string> get_property_names () const;

	virtual void set_property (const std::string& name,
			const boost::any& value);

};

} // namespace mojo

#endif
