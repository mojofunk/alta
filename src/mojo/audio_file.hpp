
#ifndef MOJO_AUDIO_FILE_INCLUDED
#define MOJO_AUDIO_FILE_INCLUDED

#include <mojo/types.hpp>
#include <mojo/audio_file_format.hpp>

namespace mojo {

class AudioFile
{
public:

	AudioFile();
	
	virtual ~AudioFile();

	virtual AudioFileFormat* format() = 0;

	virtual count_t read_frames (float* ptr, count_t frame_count) = 0;

	virtual count_t write_frames (float* ptr, count_t frame_count) = 0;

	virtual samplerate_t samplerate() const = 0;

	virtual channel_count_t channels() const = 0;
};

} // namespace mojo

#endif
