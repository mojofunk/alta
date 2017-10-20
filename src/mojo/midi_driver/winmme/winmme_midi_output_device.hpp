#ifndef MOJO_WINMME_MIDI_OUTPUT_DEVICE_H
#define MOJO_WINMME_MIDI_OUTPUT_DEVICE_H

/**
 *
 */
class WinMMEMIDIOutputDevice : public MIDIOutputDevice
{
public: // ctors
	WinMMEMIDIOutputDevice(/* TODO */);
	~WinMMEMIDIOutputDevice();

public: // MIDIDevice interface
	virtual std::string get_name() const;

	virtual error_t open(time_callback_t*, void* user_data);

	virtual error_t close();

	virtual std::string get_error_string(error_t);

public: // MIDIOutputDevice interface
	virtual error_t write(MIDIDevice::Event* buffer, int32_t size);

private: // methods
private: // data
};

#endif // MOJO_WINMME_MIDI_OUTPUT_DEVICE_H
