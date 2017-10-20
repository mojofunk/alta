#ifndef MOJO_PORTMIDI_MIDI_INPUT_DEVICE_H
#define MOJO_PORTMIDI_MIDI_INPUT_DEVICE_H

/**
 *
 */
class PortmidiMIDIInputDevice : public MIDIInputDevice
{
public: // ctors
	PortmidiMIDIInputDevice(PmDeviceID);
	~PortmidiMIDIInputDevice();

public: // MIDIDevice interface
	virtual std::string get_name() const;

	virtual error_t open(time_callback_t*, void* user_data);

	virtual error_t close();

	virtual std::string get_error_string(error_t);

public: // MIDIInputDevice interface
	virtual uint32_t read(Event* buffer, int32_t size);

private: // methods
	PmDeviceInfo const* get_device_info() const;

private: // data
	PmDeviceID m_id;
	PortMidiStream* m_stream;
};

#endif // MOJO_PORTMIDI_MIDI_INPUT_DEVICE_H
