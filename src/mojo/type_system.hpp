
#ifndef MOJO_TYPE_SYSTEM_INCLUDED
#define MOJO_TYPE_SYSTEM_INCLUDED

#include <string>
#include <typeinfo>

#include <boost/any.hpp>

#include <mojo/type_factory_ptr.hpp>

namespace mojo {

	void type_system_init ();

	void register_type (TypeFactorySPtr type);
	
	/**
	 * because std::type_info.name() is not portable between compilers
	 * etc, use a standard mapping of names to types.
	 */
	const std::string get_type_name (const std::type_info& info);

	boost::any create_type (const std::string& type_name);

}

#endif
