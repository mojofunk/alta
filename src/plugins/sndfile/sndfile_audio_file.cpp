
#include "sndfile_audio_file.hpp"
#include "sndfile_audio_file_format.hpp"

namespace mojo {

SndfileAudioFile::SndfileAudioFile()
{

}

SndfileAudioFile::~SndfileAudioFile()
{

}

AudioFileFormat*
SndfileAudioFile::format()
{
	return m_format;
}

count_t
SndfileAudioFile::read_frames(float* ptr, count_t frame_count)
{
	return sf_readf_float(m_sf, ptr, frame_count);
}

count_t
SndfileAudioFile::write_frames(float* ptr, count_t frame_count)
{
	return sf_writef_float(m_sf, ptr, frame_count);
}

samplerate_t
SndfileAudioFile::samplerate() const
{
	return m_info.samplerate;
}

channel_count_t
SndfileAudioFile::channels() const
{
	return m_info.channels;
}

} // namespace mojo
