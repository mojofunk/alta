#ifndef MOJO_MIDI_OUTPUT_DEVICE_H
#define MOJO_MIDI_OUTPUT_DEVICE_H

#include "mojo-midi-driver.hpp"

namespace mojo {

/**
 *
 */
class MIDIOutputDevice : public MIDIDevice {
public: // ctors
	virtual ~MIDIOutputDevice();

public: // MIDIDevice interface
	virtual std::string get_name() const = 0;

	virtual error_t open(time_callback_t*, void* user_data) = 0;

	virtual error_t close() = 0;

public: // MIDIOutputDevice interface
	virtual error_t write(MIDIDevice::Event* buffer, int32_t size) = 0;
};

} // namespace mojo

#endif // MOJO_MIDI_OUTPUT_DEVICE_H
