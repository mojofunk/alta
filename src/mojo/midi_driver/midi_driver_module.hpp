#ifndef MOJO_MIDI_DRIVER_MODULE_H
#define MOJO_MIDI_DRIVER_MODULE_H

namespace mojo {

/**
 *
 */
class MIDIDriverModule : public Module {
public: // ctors
	virtual ~MIDIDriverModule();

public: // Module interface
	virtual std::string get_author() = 0;

	virtual std::string get_description() = 0;

	virtual std::string get_version() = 0;

public: // interface
	virtual MIDIDriverSP create_driver() const = 0;

protected: // ctors
	MIDIDriverModule();
};

} // namespace mojo

#endif // MOJO_MIDI_DRIVER_MODULE_H
