#ifndef MOJO_PORTMIDI_MIDI_DRIVER_H
#define MOJO_PORTMIDI_MIDI_DRIVER_H

class PortmidiMIDIDriver : public MIDIDriver
{
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

#endif // MOJO_PORTMIDI_MIDI_DRIVER_H
