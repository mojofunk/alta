
#ifndef MOJO_AUDIO_DRIVER_MODULE
#define MOJO_AUDIO_DRIVER_MODULE

#include "typedefs.hpp"
#include "module.hpp"

namespace mojo {

/**
 * This is a bit wrong at the moment
 *
 * The AudioDevice class should be used for enumeration of
 * audio devices and accessing thier properties etc.
 *
 * An AudioDriver should be returned from AudioDriverModule::open
 * which takes an AudioDevice arg and other parameters.
 */
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
