
#ifndef AFL_SNDFILE_AUDIO_FILE_FORMAT_INCLUDED
#define AFL_SNDFILE_AUDIO_FILE_FORMAT_INCLUDED

#include <afl/audio_file_format.hpp>

namespace afl {

class SndfileAudioFileFormat : public AudioFileFormat
{
public:

	SndfileAudioFileFormat(int sndfile_format);

	string name() const;

	string extension() const;

private:

	int m_format;

};

} // namespace afl

#endif
