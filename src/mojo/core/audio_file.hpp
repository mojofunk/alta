
#ifndef MOJO_AUDIO_FILE
#define MOJO_AUDIO_FILE

#include "types.hpp"
#include "typedefs.hpp"

namespace mojo {

class AudioFile
{
public:

	virtual ~AudioFile();

	virtual AudioFileFormatSPtr format() = 0;

	virtual count_t read_frames (float* buf, count_t frame_count) = 0;

	virtual count_t write_frames (float* buf, count_t frame_count) = 0;

	/**
	 * @return position in frames from the start of the file
	 * @param frame_offset A frame offset from the start of the file
	 */
	virtual count_t seek (count_t frame_offset) = 0;

	/**
	 * @return The total number of frames in the audio file
	 */
	virtual count_t frames () const = 0;

	virtual samplerate_t samplerate() const = 0;

	virtual channel_count_t channels() const = 0;

protected:

	AudioFile();

};

} // namespace mojo

#endif