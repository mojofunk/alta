#ifndef MOJO_PORTMIDI_MIDI_DRIVER_H
#define MOJO_PORTMIDI_MIDI_DRIVER_H

#include "mojo-portmidi-midi-driver.hpp"

namespace mojo {

class PortmidiMIDIDriver : public MIDIDriver {
public: // ctors
	PortmidiMIDIDriver();
	~PortmidiMIDIDriver();

public: // MIDIDriver interface
	MIDIInputDeviceSPSet get_input_devices();

	MIDIOutputDeviceSPSet get_output_devices();

private: // methods
	bool initialize();
	bool terminate();

	void refresh_devices();

private: // member data
	bool m_initialized;

	MIDIInputDeviceSPSet m_inputs;

	MIDIOutputDeviceSPSet m_outputs;
};

} // namespace mojo

#endif // MOJO_PORTMIDI_MIDI_DRIVER_H
