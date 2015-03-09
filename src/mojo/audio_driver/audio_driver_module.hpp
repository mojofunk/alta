#ifndef MOJO_AUDIO_DRIVER_MODULE_H
#define MOJO_AUDIO_DRIVER_MODULE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/modules/module.hpp"
#include "mojo/audio_driver/typedefs.hpp"
#endif

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
