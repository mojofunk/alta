
#ifndef AFL_SNDFILE_AUDIO_FILE_INCLUDED
#define AFL_SNDFILE_AUDIO_FILE_INCLUDED

#include <sndfile.h>

#include <afl/audio_file.hpp>

namespace afl {

class SndfileAudioFile : public AudioFile
{
	public:

		SndfileAudioFile();

        virtual ~SndfileAudioFile();

        virtual count_t read_frames (float* ptr, count_t frame_count);

        virtual count_t write_frames (float* ptr, count_t frame_count);

	private:

		SNDFILE* m_sf;
		SF_INFO m_info;
};

} // namespace afl

#endif
