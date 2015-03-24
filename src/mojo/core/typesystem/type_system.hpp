#ifndef MOJO_TYPE_SYSTEM_H
#define MOJO_TYPE_SYSTEM_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/typesystem/typedefs.hpp"
#endif

namespace mojo {

// namespace?
class TypeSystem
{
public:

	static void initialize ();

	static void deinitialize ();

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

#endif // MOJO_TYPE_SYSTEM_H
