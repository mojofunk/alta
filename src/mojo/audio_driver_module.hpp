
#ifndef MOJO_AUDIO_DRIVER_MODULE
#define MOJO_AUDIO_DRIVER_MODULE

#include <set>

#include <mojo/module.hpp>

#include <mojo/audio_device.hpp>

namespace mojo {

class AudioDriverModule : public Module
{
public: // typedefs

	typedef std::set<AudioDevice*> Devices;

public: // ctors

	virtual ~AudioDriverModule ();

public: // interface

	virtual Devices get_devices () const = 0;

protected: // ctors

	AudioDriverModule ();

};

} // namespace mojo

#endif
