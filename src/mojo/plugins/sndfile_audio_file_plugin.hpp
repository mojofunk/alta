
#ifndef MOJO_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED

#include <mojo/audio_file_plugin.hpp>

namespace mojo {

class SndfileAudioFilePlugin : public AudioFilePlugin
{
public:
	virtual std::string get_author();

	virtual std::string get_description();

	virtual std::string get_version();

	virtual AudioFile * create();

};

}

#endif
