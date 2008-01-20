
#ifndef MOJO_SNDFILE_AUDIO_FILE_INCLUDED
#define MOJO_SNDFILE_AUDIO_FILE_INCLUDED

#include <sndfile.h>

#include <mojo/audio_file.hpp>
#include <mojo/audio_file_format.hpp>

#include <stdexcept>

namespace mojo {

class SndfileAudioFileFormat;

class SndfileException : public std::runtime_error
{
public:
	SndfileException (const string& what)
		: std::runtime_error (what) { }
};

class SndfileAudioFile : public AudioFile
{
public:

	SndfileAudioFile(const string& path);

	virtual ~SndfileAudioFile();

	virtual AudioFileFormat* format();

	virtual count_t read_frames (float* ptr, count_t frame_count);

	virtual count_t write_frames (float* ptr, count_t frame_count);

	virtual samplerate_t samplerate() const;

	virtual channel_count_t channels() const;

private:

	const string m_path;

	SNDFILE* m_sf;
	SF_INFO m_info;

	SndfileAudioFileFormat* m_format;

};

} // namespace mojo

#endif
