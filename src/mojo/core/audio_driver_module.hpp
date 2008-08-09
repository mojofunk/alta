
#ifndef MOJO_AUDIO_DRIVER_MODULE
#define MOJO_AUDIO_DRIVER_MODULE

#include "typedefs.hpp"
#include "module.hpp"

namespace mojo {

class AudioDriverModule : public Module
{
public: // ctors

	virtual ~AudioDriverModule ();

public: // interface

	virtual AudioDeviceSet get_devices () const = 0;

protected: // ctors

	AudioDriverModule ();

};

} // namespace mojo

#endif
