#ifndef MOJO_MODULE_H
#define MOJO_MODULE_H

/**
 * Base class for all modules
 *
 * Should there be a ModuleInfo class?
 */
class Module
{
public: // typedefs
	typedef void* (*factory_func_t)(void);

public: // Constructors
	virtual ~Module();

public: // Module Interface
	virtual std::string get_author() = 0;

	virtual std::string get_description() = 0;

	virtual std::string get_version() = 0;
};

#endif // MOJO_MODULE_H
