
#ifndef MOJO_AUDIO_FILE_PTR_INCLUDED
#define MOJO_AUDIO_FILE_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioFile;

	typedef boost::shared_ptr<AudioFile>    AudioFileSPtr;
	typedef boost::weak_ptr<AudioFile>      AudioFileWPtr;

} // namespace mojo

#endif
