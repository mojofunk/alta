
#include <typeinfo>

#include <mojo/register_types.hpp>
#include <mojo/type_system.hpp>
#include <mojo/type_names.hpp>

namespace mojo {

void
register_types()
{
	register_type_name (typeid(int), int_type_name);
	register_type_name (typeid(float), float_type_name);
	register_type_name (typeid(std::string), string_type_name);

}

}
