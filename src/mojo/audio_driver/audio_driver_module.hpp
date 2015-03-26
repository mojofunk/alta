#ifndef MOJO_AUDIO_DRIVER_MODULE_H
#define MOJO_AUDIO_DRIVER_MODULE_H

#include "mojo-audio-driver.hpp"

namespace mojo {

/**
 *
 */
class AudioDriverModule : public Module {
public: // ctors
	virtual ~AudioDriverModule();

public: // interface
	virtual AudioDriverSP create_driver() const = 0;

protected: // ctors
	AudioDriverModule();
};

} // namespace mojo

#endif // MOJO_AUDIO_DRIVER_MODULE_H
