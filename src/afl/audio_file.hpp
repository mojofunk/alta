
#ifndef AFL_AUDIO_FILE_INCLUDED
#define AFL_AUDIO_FILE_INCLUDED

#include <afl/types.hpp>
#include <afl/audio_file_format.hpp>

namespace afl {

class AudioFile
{
public:

	virtual ~AudioFile() { }

	virtual AudioFileFormat* format() = 0;

	virtual count_t read_frames (float* ptr, count_t frame_count) = 0;

	virtual count_t write_frames (float* ptr, count_t frame_count) = 0;

};

} // namespace afl

#endif
