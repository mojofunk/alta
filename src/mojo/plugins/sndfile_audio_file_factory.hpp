
#ifndef MOJO_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED

#include <mojo/audio_file_factory.hpp>

namespace mojo {

class SndfileAudioFileFactory : public AudioFileFactory
{
public:

	virtual ~SndfileAudioFileFactory();

	virtual string name () const;

	virtual AudioFile * create();

};

}

#endif
