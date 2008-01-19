
#ifndef MOJO_AUDIO_FILE_FORMAT_INCLUDED
#define MOJO_AUDIO_FILE_FORMAT_INCLUDED

#include <string>

namespace mojo {

using std::string;

class AudioFileFormat
{
public:

	AudioFileFormat();

	virtual ~AudioFileFormat();

	virtual string name() const = 0;

	virtual string extension() const = 0;

};

} // namespace mojo

#endif
