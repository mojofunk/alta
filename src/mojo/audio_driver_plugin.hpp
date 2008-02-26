
#ifndef MOJO_AUDIO_DRIVER_PLUGIN_INCLUDED
#define MOJO_AUDIO_DRIVER_PLUGIN_INCLUDED

#include <set>

#include <mojo/plugin.hpp>

#include <mojo/audio_device.hpp>

namespace mojo {

class AudioDriverPlugin : public Plugin
{
public: // typedefs

	typedef std::set<AudioDevice*> AudioDevices;

public: // ctors

	virtual ~AudioDriverPlugin();

public: // interface

	virtual AudioDevices get_devices () const = 0;

protected: // ctors

	AudioDriverPlugin();

};

} // namespace mojo

#endif
