
#ifndef MOJO_TYPE_SYSTEM_INCLUDED
#define MOJO_TYPE_SYSTEM_INCLUDED

#include <string>
#include <typeinfo>

#include <boost/any.hpp>

namespace mojo {

	void type_system_init ();

	void register_type_name (const std::type_info& info,
			const std::string& type_name);
	
	/**
	 * because std::type_info.name() is not portable between compilers
	 * etc, use a standard mapping of names to types.
	 */
	const std::string get_type_name (const std::type_info& info);

	typedef boost::any (*type_factory_func_t) ();

	void register_type_factory (type_factory_func_t func,
			const std::string& type_name);
}

#endif
