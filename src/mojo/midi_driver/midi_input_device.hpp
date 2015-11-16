#ifndef MOJO_MIDI_INPUT_DEVICE_H
#define MOJO_MIDI_INPUT_DEVICE_H

namespace mojo {

/**
 *
 */
class MIDIInputDevice : public MIDIDevice {
public: // ctors
	virtual ~MIDIInputDevice();

public: // MIDIDevice interface
	/// @return The name of the device. unique??
	virtual std::string get_name() const = 0;

	virtual error_t open(time_callback_t*, void* user_data) = 0;

	virtual error_t close() = 0;

public: // MIDIInputDevice interface
	// error handling?
	virtual uint32_t read(Event* buffer, int32_t size) = 0;
};

} // namespace mojo

#endif // MOJO_MIDI_INPUT_DEVICE_H
