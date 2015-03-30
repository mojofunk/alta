#ifndef MOJO_MIDI_DEVICE_H
#define MOJO_MIDI_DEVICE_H

#include "mojo-midi-driver.hpp"

namespace mojo {

/**
 *
 */
class MIDIDevice {
public: // ctors
	virtual ~MIDIDevice();

public: // types
	typedef int32_t timestamp_t;
	typedef int32_t midi_message_t;

	struct Event {
		midi_message_t message;
		timestamp_t timestamp;
	};

	using time_callback_t = timestamp_t(void* user_data);

	enum error_t { NO_ERROR = 0, UNKNOWN_ERROR = -1000 };

public: // MIDIDevice interface
	/// @return The name of the device. unique??
	virtual std::string get_name() const = 0;

	virtual error_t open(time_callback_t*, void* user_data) = 0;

	virtual error_t close() = 0;
};

} // namespace mojo

#endif // MOJO_MIDI_DEVICE_H
