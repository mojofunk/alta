#ifndef MOJO_PORTMIDI_MIDI_INPUT_DEVICE_H
#define MOJO_PORTMIDI_MIDI_INPUT_DEVICE_H

#include "mojo-portmidi-midi-driver.hpp"

namespace mojo {

/**
 *
 */
class PortmidiMIDIInputDevice : public MIDIInputDevice {
public: // ctors
	PortmidiMIDIInputDevice(PmDeviceID);
	~PortmidiMIDIInputDevice();

public: // MIDIDevice interface
	virtual std::string get_name() const;

	virtual error_t open(time_callback_t*, void* user_data);

	virtual error_t close();

public: // MIDIInputDevice interface
	virtual uint32_t read(Event* buffer, int32_t size);

private: // methods
	PmDeviceInfo const* get_device_info() const;

private: // data
	PmDeviceID m_id;
	PortMidiStream* m_stream;
};

} // namespace mojo

#endif // MOJO_PORTMIDI_MIDI_INPUT_DEVICE_H
