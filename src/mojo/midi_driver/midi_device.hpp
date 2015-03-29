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

public: // interface
	enum callback_result_t { CONTINUE = 0, ABORT };

	enum error_t { NO_ERROR = 0, UNKNOWN_ERROR = -1000 };

	using callback_t = callback_result_t(const float* input_buffer,
	                                     const float* output_buffer,
	                                     count_t frames,
	                                     void* user_data);

	/// @return The name of the device. unique??
	virtual std::string get_name() const = 0;

	virtual bool is_input() const = 0;

	virtual bool is_output() const = 0;

};

} // namespace mojo

#endif // MOJO_MIDI_DEVICE_H
