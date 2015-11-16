#ifndef MOJO_WINMME_MIDI_DRIVER_H
#define MOJO_WINMME_MIDI_DRIVER_H

namespace mojo {

class WinMMEMIDIDriver : public MIDIDriver {
public: // ctors
	WinMMEMIDIDriver();
	~WinMMEMIDIDriver();

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

#endif // MOJO_WINMME_MIDI_DRIVER_H
