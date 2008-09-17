
#ifndef MOJO_TYPE_SYSTEM
#define MOJO_TYPE_SYSTEM

#include <string>
#include <typeinfo>

#include <boost/any.hpp>

#include <mojo/typesystem/typedefs.hpp>

namespace mojo {

class TypeSystem
{
public:

	static TypeSystemSP init ();

	static void register_type (TypeFactorySP type);
	
	/**
	 * because std::type_info.name() is not portable between compilers
	 * etc, use a standard mapping of names to types.
	 */
	static const std::string get_type_name (const std::type_info& info);

	static boost::any create_type (const std::string& type_name);

private:

	TypeSystem();

	~TypeSystem();

private:

	static TypeSystem* s_type_system;

private:

	struct deleter;
	friend struct deleter;

	struct deleter
	{
		void operator()(TypeSystem* type_system)
		{ delete type_system; s_type_system = 0; }
	};
};

} // namespace mojo

#endif
