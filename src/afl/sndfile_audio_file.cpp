
#include <afl/sndfile_audio_file.hpp>

namespace afl {

SndfileAudioFile::SndfileAudioFile()
{

}

SndfileAudioFile::~SndfileAudioFile()
{

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

} // namespace afl
