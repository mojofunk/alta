#ifndef MOJO_AUDIO_FILE_FORMAT_H
#define MOJO_AUDIO_FILE_FORMAT_H

#include <string>

namespace mojo {

using std::string;

class AudioFileFormat
{
public:

	virtual ~AudioFileFormat();

	virtual string name() const = 0;

	virtual string extension() const = 0;

protected:

	AudioFileFormat();

};

} // namespace mojo

#endif // MOJO_AUDIO_FILE_FORMAT_H
