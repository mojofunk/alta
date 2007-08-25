
#ifndef AFL_AUDIO_FILE_FACTORY_INCLUDED
#define AFL_AUDIO_FILE_FACTORY_INCLUDED

#include <afl/audio_file.hpp>

namespace afl {

class AudioFileFactory
{
public:

	virtual ~AudioFileFactory();

	virtual AudioFile * create() = 0;

};

} // namespace afl

#endif
