
#include "sndfile_audio_file.hpp"
#include "sndfile_audio_file_format.hpp"

namespace mojo {

SndfileAudioFile::SndfileAudioFile(const string& path)
	:
		m_path(path),
		m_sf(0),
		m_format(0)
{
	m_sf = sf_open (path.c_str(), SFM_RDWR, &m_info);

	if (m_sf == NULL)
		throw SndfileException (sf_strerror (m_sf));

	m_format = new SndfileAudioFileFormat(m_info.format);
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
