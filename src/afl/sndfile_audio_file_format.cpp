
#include <afl/sndfile_audio_file_format.hpp>

namespace afl {

SndfileAudioFileFormat::SndfileAudioFileFormat(int sndfile_format)
	:
		m_format(sndfile_format)
	{ }

string name()
{
	return "";
}

string extension()
{
	return "";
}

} // namespace afl