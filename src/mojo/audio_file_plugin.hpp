
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

	/**
	 * return new AudioFile or 0 on failure
	 */
	virtual AudioFile * open (const std::string& path) = 0;

};

} // namespace mojo

#endif
