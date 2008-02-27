
#ifndef MOJO_AUDIO_DRIVER_PLUGIN_PTR_INCLUDED
#define MOJO_AUDIO_DRIVER_PLUGIN_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class AudioDriverPlugin;

	typedef boost::shared_ptr<AudioDriverPlugin>    AudioDriverPluginSPtr;
	typedef boost::weak_ptr<AudioDriverPlugin>      AudioDriverPluginWPtr;

} // namespace mojo

#endif
