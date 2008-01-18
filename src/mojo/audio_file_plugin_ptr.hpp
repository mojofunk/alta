
#ifndef MOJO_AUDIO_FILE_PLUGIN_PTR_INCLUDED
#define MOJO_AUDIO_FILE_PLUGIN_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioFilePlugin;

	typedef boost::shared_ptr<AudioFilePlugin>    AudioFilePluginSPtr;
	typedef boost::weak_ptr<AudioFilePlugin>      AudioFilePluginWPtr;

} // namespace mojo

#endif
