#ifndef MOJO_AUDIO_DRIVER_MODULE_H
#define MOJO_AUDIO_DRIVER_MODULE_H

#include "typedefs.hpp"
#include "module.hpp"

namespace mojo {

/**
 *
 */
class AudioDriverModule : public Module
{
public: // ctors

	virtual ~AudioDriverModule ();

public: // interface

	virtual AudioDeviceSPSet get_devices () const = 0;

protected: // ctors

	AudioDriverModule ();

};

} // namespace mojo

#endif // MOJO_AUDIO_DRIVER_MODULE_H
