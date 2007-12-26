
#ifndef MOJO_AUDIO_FILE_FORMAT_INCLUDED
#define MOJO_AUDIO_FILE_FORMAT_INCLUDED

#include <string>

namespace mojo {

using std::string;

class AudioFileFormat
{
public:

	virtual ~AudioFileFormat() { }

	virtual string name() = 0;

	virtual string extension() = 0;

};

} // namespace mojo

#endif
