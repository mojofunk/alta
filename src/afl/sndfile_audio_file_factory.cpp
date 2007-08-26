
#include <afl/sndfile_audio_file_factory.hpp>
#include <afl/sndfile_audio_file.hpp>

#include <afl/export.h>

namespace afl {

SndfileAudioFileFactory::~SndfileAudioFileFactory()
{


}

AudioFile*
SndfileAudioFileFactory::create()
{
	return new SndfileAudioFile;
}

extern "C" AFL_API void * factory(void)
{
	return new SndfileAudioFileFactory;

}

} // namespace afl
