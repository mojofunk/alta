
#ifndef MOJO_SNDFILE_AUDIO_FILE_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_INCLUDED

#include <sndfile.h>

#include <mojo/audio_file.hpp>
#include <mojo/audio_file_format.hpp>

namespace mojo {

class SndfileAudioFileFormat;

class SndfileAudioFile : public AudioFile
{
public:

	SndfileAudioFile();

	virtual ~SndfileAudioFile();

	virtual AudioFileFormat* format();

	virtual count_t read_frames (float* ptr, count_t frame_count);

	virtual count_t write_frames (float* ptr, count_t frame_count);

	virtual samplerate_t samplerate() const;

	virtual channel_count_t channels() const;

private:

	SNDFILE* m_sf;
	SF_INFO m_info;

	SndfileAudioFileFormat* m_format;

};

} // namespace mojo

#endif
