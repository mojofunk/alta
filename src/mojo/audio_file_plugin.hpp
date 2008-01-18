
#ifndef MOJO_AUDIO_FILE_PLUGIN_INCLUDED
#define MOJO_AUDIO_FILE_PLUGIN_INCLUDED

#include <string>

#include <mojo/plugin.hpp>

#include <mojo/audio_file.hpp>

namespace mojo {

class AudioFilePlugin : public Plugin
{
public:

	AudioFilePlugin();
	~AudioFilePlugin();

	virtual AudioFile * create() = 0;

};

} // namespace mojo

#endif
