
#include <afl/sndfile_audio_file_factory.hpp>
#include <afl/sndfile_audio_file.hpp>

namespace afl {

SndfileAudioFileFactory::~SndfileAudioFileFactory()
{


}

AudioFile*
SndfileAudioFileFactory::create()
{
	return new SndfileAudioFile();
}

} // namespace afl
