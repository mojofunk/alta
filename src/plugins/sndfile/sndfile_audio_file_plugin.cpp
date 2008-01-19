
#include "sndfile_audio_file_plugin.hpp"
#include "sndfile_audio_file.hpp"

#include <mojo/export.h>

namespace mojo {

std::string
SndfileAudioFilePlugin::get_author()
{
	return "Tim Mayberry";
}

std::string
SndfileAudioFilePlugin::get_description()
{
	return "libsndfile plugin";
}

std::string
SndfileAudioFilePlugin::get_version()
{
	return "0.0.1";
}

AudioFile*
SndfileAudioFilePlugin::open (const std::string& path)
{
	return new SndfileAudioFile;
}

MOJO_CAPI void * mojo_plugin_factory(void)
{
	return new SndfileAudioFilePlugin;
}

} // namespace mojo
