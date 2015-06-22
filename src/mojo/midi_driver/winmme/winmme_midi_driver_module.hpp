#ifndef MOJO_WINMME_MIDI_DRIVER_MODULE_H
#define MOJO_WINMME_MIDI_DRIVER_MODULE_H

#include "mojo-winmme-midi-driver.hpp"

namespace mojo {

/**
 *
 */
class WinMMEMIDIDriverModule : public MIDIDriverModule {
public: // ctors
	WinMMEMIDIDriverModule();
	~WinMMEMIDIDriverModule();

public: // Module interface
	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

public: // interface
	virtual MIDIDriverSP create_driver() const;
};

} // namespace mojo

#endif // MOJO_WINMME_MIDI_DRIVER_MODULE_H
