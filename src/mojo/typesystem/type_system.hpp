#ifndef MOJO_TYPE_SYSTEM
#define MOJO_TYPE_SYSTEM

#include <string>
#include <typeinfo>

#include <boost/any.hpp>

#include "typedefs.hpp"

namespace mojo {

// namespace?
class TypeSystem
{
public:

	static void register_type (TypeFactorySP type);
	
	/**
	 * because std::type_info.name() is not portable between compilers
	 * etc, use a standard mapping of names to types.
	 */
	static const std::string get_type_name (const std::type_info& info);

	/**
	 * Given a portable type name create a specific instance of that
	 * type
	 */
	static boost::any create_type (const std::string& type_name);

};

} // namespace mojo

#endif
