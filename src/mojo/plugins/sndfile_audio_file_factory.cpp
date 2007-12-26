
#include "sndfile_audio_file_factory.hpp"
#include "sndfile_audio_file.hpp"

#include <mojo/export.h>

namespace mojo {

SndfileAudioFileFactory::~SndfileAudioFileFactory()
{


}

string
SndfileAudioFileFactory::name() const
{
	return "libsndfile";
}

AudioFile*
SndfileAudioFileFactory::create()
{
	return new SndfileAudioFile;
}

MOJO_CAPI void * factory(void)
{
	return new SndfileAudioFileFactory;
}

} // namespace mojo
