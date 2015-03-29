#ifndef MOJO_PORTMIDI_MIDI_DEVICE_H
#define MOJO_PORTMIDI_MIDI_DEVICE_H

#include "mojo-portmidi-midi-driver.hpp"

namespace mojo {

/**
 *
 */
class PortmidiMIDIDevice : public MIDIDevice {
public: // ctors
	PortmidiMIDIDevice(PmDeviceID);
	~PortmidiMIDIDevice();

public: // interface
	enum callback_result_t { CONTINUE = 0, ABORT };

	enum error_t { NO_ERROR = 0, UNKNOWN_ERROR = -1000 };

	using callback_t = callback_result_t(const float* input_buffer,
	                                     const float* output_buffer,
	                                     count_t frames,
	                                     void* user_data);

	virtual std::string get_name() const;

private: // methods
	PmDeviceInfo const* get_device_info() const;

private: // data
	PmDeviceID m_id;
};

} // namespace mojo

#endif // MOJO_PORTMIDI_MIDI_DEVICE_H
