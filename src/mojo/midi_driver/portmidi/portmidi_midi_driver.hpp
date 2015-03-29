#ifndef MOJO_PORTMIDI_MIDI_DRIVER_H
#define MOJO_PORTMIDI_MIDI_DRIVER_H

#include "mojo-portmidi-midi-driver.hpp"

namespace mojo {

class PortmidiMIDIDriver : public MIDIDriver {
public: // ctors
	PortmidiMIDIDriver();
	~PortmidiMIDIDriver();

public: // AudioDriver interface
	MIDIDeviceSPSet get_devices() const;

private: // methods
	bool initialize();
	bool terminate();

	static void discover_devices(MIDIDeviceSPSet& devices);

private: // member data
	bool m_initialized;
};

} // namespace mojo

#endif // MOJO_PORTMIDI_MIDI_DRIVER_H
