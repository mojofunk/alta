
#ifndef MOJO_SNDFILE_AUDIO_FILE
#define MOJO_SNDFILE_AUDIO_FILE

#include <sndfile.h>

#include <mojo/mojo.hpp>

#include <stdexcept>

namespace mojo {

class SndfileException : public std::runtime_error
{
public:
	SndfileException (const std::string& what)
		: std::runtime_error (what) { }
};

class SndfileAudioFile : public AudioFile
{
public:

	SndfileAudioFile(const std::string& path);

	virtual ~SndfileAudioFile();

	virtual AudioFileFormatSP format();

	virtual count_t read_frames (float* buf, count_t frame_count);

	virtual count_t write_frames (float* buf, count_t frame_count);

	virtual count_t seek (count_t frame_offset);

	virtual count_t frames () const;

	virtual samplerate_t samplerate() const;

	virtual channel_count_t channels() const;

private:

	const std::string m_path;

	SNDFILE* m_sf;
	SF_INFO m_info;

	AudioFileFormatSP m_format;

};

} // namespace mojo

#endif
