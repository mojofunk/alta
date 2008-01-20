
#include "sndfile_audio_file_plugin.hpp"
#include "sndfile_audio_file.hpp"

#include <mojo/export.h>

#include <iostream>

namespace mojo {

SndfileAudioFilePlugin::SndfileAudioFilePlugin()
{

}

SndfileAudioFilePlugin::~SndfileAudioFilePlugin()
{

}

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
	SndfileAudioFile* audio_file = 0;

	try
	{
		audio_file = new SndfileAudioFile(path);
	}
	catch(const SndfileException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return audio_file;
}

AudioFilePlugin::Formats
SndfileAudioFilePlugin::get_readable_formats () const
{
	return m_readable_formats;
}

MOJO_CAPI void * mojo_plugin_factory(void)
{
	return new SndfileAudioFilePlugin;
}

} // namespace mojo
