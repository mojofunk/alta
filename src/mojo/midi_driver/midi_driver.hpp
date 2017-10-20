#ifndef MOJO_MIDI_DRIVER_H
#define MOJO_MIDI_DRIVER_H

class MIDIDriver
{
public: // ctors
	virtual ~MIDIDriver();

public: // interface
	virtual MIDIInputDeviceSPSet get_input_devices() = 0;

	virtual MIDIOutputDeviceSPSet get_output_devices() = 0;

protected: // ctors
	MIDIDriver();
};

#endif // MOJO_MIDI_DRIVER_H
