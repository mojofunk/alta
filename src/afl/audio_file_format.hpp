
#ifndef AFL_AUDIO_FILE_FORMAT_INCLUDED
#define AFL_AUDIO_FILE_FORMAT_INCLUDED

#include <string>

namespace afl {

using std::string;

class AudioFileFormat
{
public:

	virtual ~AudioFileFormat() { }

	virtual string name() = 0;

	virtual string extension() = 0;

};

} // namespace afl

#endif
