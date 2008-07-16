
#ifndef MOJO_MODULE
#define MOJO_MODULE

#include <string>

namespace mojo {

/**
 * Base class for all modules
 *
 * Should there be a ModuleInfo class?
 */
class Module
{
public:

	virtual ~Module() { }

	virtual std::string get_author () = 0;

	virtual std::string get_description () = 0;

	virtual std::string get_version () = 0;

};

typedef void * (*module_func_t) (void);

} // namespace mojo

#endif
