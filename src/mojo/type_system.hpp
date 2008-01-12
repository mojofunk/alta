
#ifndef MOJO_TYPE_SYSTEM_INCLUDED
#define MOJO_TYPE_SYSTEM_INCLUDED

#include <string>
#include <typeinfo>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <mojo/type_factory_ptr.hpp>

namespace mojo {

class TypeSystem;

typedef boost::shared_ptr<TypeSystem>    TypeSystemSPtr;

class TypeSystem
{
public:

	static TypeSystemSPtr create ();

	static void register_type (TypeFactorySPtr type);
	
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

}

#endif
