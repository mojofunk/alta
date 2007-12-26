
#ifndef MOJO_AUDIO_FILE_FACTORY_INCLUDED
#define MOJO_AUDIO_FILE_FACTORY_INCLUDED

#include <string>

#include <mojo/audio_file.hpp>

namespace mojo {

using std::string;

class AudioFileFactory
{
public:

	virtual ~AudioFileFactory() { }

	virtual string name() const = 0;

	virtual AudioFile * create() = 0;

};

typedef void * (*factory_func_t) (void);

} // namespace mojo

#endif
