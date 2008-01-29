
#ifndef MOJO_AUDIO_DRIVER_PLUGIN_INCLUDED
#define MOJO_AUDIO_DRIVER_PLUGIN_INCLUDED

#include <mojo/plugin.hpp>

namespace mojo {

class AudioDriverPlugin : public Plugin
{
public: // ctors

	virtual ~AudioDriverPlugin();

protected: // ctors

	AudioDriverPlugin();

};

} // namespace mojo

#endif
