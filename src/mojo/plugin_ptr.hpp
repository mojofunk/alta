
#ifndef MOJO_PLUGIN_PTR_INCLUDED
#define MOJO_PLUGIN_PTR_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace mojo {

	class Plugin;

	typedef boost::shared_ptr<Plugin>    PluginSPtr;
	typedef boost::weak_ptr<Plugin>      PluginWPtr;

} // namespace mojo

#endif
