#ifndef MOJO_PORTMIDI_MIDI_DRIVER_MODULE_H
#define MOJO_PORTMIDI_MIDI_DRIVER_MODULE_H

namespace mojo {

/**
 *
 */
class PortmidiMIDIDriverModule : public MIDIDriverModule {
public: // ctors
	PortmidiMIDIDriverModule();
	~PortmidiMIDIDriverModule();

public: // Module interface
	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // interface
	virtual MIDIDriverSP create_driver() const;
};

} // namespace mojo

#endif // MOJO_PORTMIDI_MIDI_DRIVER_MODULE_H
