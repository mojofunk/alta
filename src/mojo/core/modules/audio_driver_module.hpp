#ifndef MOJO_AUDIO_DRIVER_MODULE_H
#define MOJO_AUDIO_DRIVER_MODULE_H

#include "mojo/core/interfaces/typedefs.hpp"

#include "mojo/core/modules/module.hpp"

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