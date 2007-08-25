
#ifndef AFL_SNDFILE_AUDIO_FILE_INCLUDED
#define AFL_SNDFILE_AUDIO_FILE_INCLUDED

#include <sndfile.h>

#include <afl/audio_file.hpp>
#include <afl/audio_file_format.hpp>

namespace afl {

class SndfileAudioFileFormat;

class SndfileAudioFile : public AudioFile
{
public:

	SndfileAudioFile();

	virtual ~SndfileAudioFile();

	virtual AudioFileFormat* format();

	virtual count_t read_frames (float* ptr, count_t frame_count);

	virtual count_t write_frames (float* ptr, count_t frame_count);

private:

	SNDFILE* m_sf;
	SF_INFO m_info;

	SndfileAudioFileFormat* m_format;
};

} // namespace afl

#endif
