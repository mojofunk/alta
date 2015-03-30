#ifndef MOJO_MIDI_DRIVER_H
#define MOJO_MIDI_DRIVER_H

#include "mojo-midi-driver.hpp"

namespace mojo {

class MIDIDriver {
public: // ctors
	virtual ~MIDIDriver();

public: // interface
	virtual MIDIInputDeviceSPSet get_input_devices() = 0;

	virtual MIDIOutputDeviceSPSet get_output_devices() = 0;

protected: // ctors
	MIDIDriver();
};

} // namespace mojo

#endif // MOJO_MIDI_DRIVER_H
