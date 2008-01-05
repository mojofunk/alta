
#ifndef MOJO_SNDFILE_AUDIO_FILE_FORMAT_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_FORMAT_INCLUDED

#include <mojo/audio_file_format.hpp>

namespace mojo {

class SndfileAudioFileFormat : public AudioFileFormat
{
public:

	SndfileAudioFileFormat(int sndfile_format);

	string name() const;

	string extension() const;

private:

	int m_format;

};

} // namespace mojo

#endif
