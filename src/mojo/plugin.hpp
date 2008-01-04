
#ifndef MOJO_PLUGIN_INCLUDED
#define MOJO_PLUGIN_INCLUDED

#include <string>

namespace mojo {

/**
 * Base class for all plugins
 *
 * Should there be a PluginInfo class
 */
class Plugin
{
public:

	virtual ~Plugin() { }

	virtual std::string get_author() = 0;

	virtual std::string get_description() = 0;

	virtual std::string get_version() = 0;

};

typedef void * (*plugin_func_t) (void);

} // namespace mojo
#endif
