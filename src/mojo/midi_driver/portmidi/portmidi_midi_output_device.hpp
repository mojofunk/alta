#ifndef MOJO_PORTMIDI_MIDI_OUTPUT_DEVICE_H
#define MOJO_PORTMIDI_MIDI_OUTPUT_DEVICE_H

/**
 *
 */
class PortmidiMIDIOutputDevice : public MIDIOutputDevice
{
public: // ctors
	PortmidiMIDIOutputDevice(PmDeviceID);
	~PortmidiMIDIOutputDevice();

public: // MIDIDevice interface
	virtual std::string get_name() const;

	virtual error_t open(time_callback_t*, void* user_data);

	virtual error_t close();

	virtual std::string get_error_string(error_t);

public: // MIDIOutputDevice interface
	virtual error_t write(MIDIDevice::Event* buffer, int32_t size);

private: // methods
	PmDeviceInfo const* get_device_info() const;

private: // data
	PmDeviceID m_id;
	PortMidiStream* m_stream;
};

#endif // MOJO_PORTMIDI_MIDI_OUTPUT_DEVICE_H
