
#ifndef MOJO_MIDI_TRACK_PTR_INCLUDED
#define MOJO_MIDI_TRACK_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class MidiTrack;

	typedef boost::shared_ptr<MidiTrack>    MidiTrackSPtr;
	typedef boost::weak_ptr<MidiTrack>      MidiTrackWPtr;

} // namespace mojo

#endif
