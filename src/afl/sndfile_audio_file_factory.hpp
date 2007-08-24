
#ifndef AFL_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED
#define AFL_SNDFILE_AUDIO_FILE_FACTORY_INCLUDED

#include <afl/audio_file_factory.hpp>

namespace afl {

class SndfileAudioFileFactory : public AudioFileFactory
{
	public:

		virtual ~SndfileAudioFileFactory();

		virtual AudioFile * create();

};

}

#endif
