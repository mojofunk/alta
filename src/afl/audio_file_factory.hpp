
#ifndef AFL_AUDIO_FILE_FACTORY_INCLUDED
#define AFL_AUDIO_FILE_FACTORY_INCLUDED

#include <string>

#include <afl/audio_file.hpp>

namespace afl {

using std::string;

class AudioFileFactory
{
public:

	virtual ~AudioFileFactory() { }

	virtual string name() const = 0;

	virtual AudioFile * create() = 0;

};

typedef void * (*factory_func_t) (void);

} // namespace afl

#endif
