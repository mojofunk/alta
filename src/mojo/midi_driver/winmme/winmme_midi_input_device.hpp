#ifndef MOJO_WINMME_MIDI_INPUT_DEVICE_H
#define MOJO_WINMME_MIDI_INPUT_DEVICE_H

#include "mojo-winmme-midi-driver.hpp"

namespace mojo {

/**
 *
 */
class WinMMEMIDIInputDevice : public MIDIInputDevice {
public: // ctors
	WinMMEMIDIInputDevice(/*TODO*/);
	~WinMMEMIDIInputDevice();

public: // MIDIDevice interface
	virtual std::string get_name() const;

	virtual error_t open(time_callback_t*, void* user_data);

	virtual error_t close();

	virtual std::string get_error_string(error_t);

public: // MIDIInputDevice interface
	virtual uint32_t read(Event* buffer, int32_t size);

private: // methods
private: // data
};

} // namespace mojo

#endif // MOJO_WINMME_MIDI_INPUT_DEVICE_H