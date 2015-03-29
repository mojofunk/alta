#ifndef MOJO_MIDI_DRIVER_H
#define MOJO_MIDI_DRIVER_H

#include "mojo-midi-driver.hpp"

namespace mojo {

class MIDIDriver {
public: // ctors
	virtual ~MIDIDriver();

public: // interface
	virtual MIDIDeviceSPSet get_devices() const = 0;

protected: // ctors
	MIDIDriver();
};

} // namespace mojo

#endif // MOJO_MIDI_DRIVER_H
