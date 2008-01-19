
#include "sndfile_audio_file_format.hpp"

namespace mojo {

SndfileAudioFileFormat::SndfileAudioFileFormat(int sndfile_format)
	:
		m_format(sndfile_format)
	{ }

string
SndfileAudioFileFormat::name() const
{
	return "none";
}

string
SndfileAudioFileFormat::extension() const
{
	return ".none";
}

} // namespace mojo
