#ifndef MOJO_MODULE_H
#define MOJO_MODULE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

/**
 * Base class for all modules
 *
 * Should there be a ModuleInfo class?
 */
class Module {
public: // typedefs
	typedef void* (*factory_func_t)(void);

public: // Constructors
	virtual ~Module();

public: // Module Interface
	virtual std::string get_author() = 0;

	virtual std::string get_description() = 0;

	virtual std::string get_version() = 0;
};

} // namespace mojo

#endif // MOJO_MODULE_H
