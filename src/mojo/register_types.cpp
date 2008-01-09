
#include <typeinfo>

#include <mojo/register_types.hpp>
#include <mojo/type_system.hpp>
#include <mojo/type_names.hpp>

namespace mojo {

boost::any
int_factory ()
{
	int i = 0;
	return boost::any(i);
}

boost::any
float_factory ()
{
	float f = 0;
	return boost::any(f);
}

boost::any
string_factory ()
{
	std::string s;
	return boost::any(s);
}

void
register_types()
{
	register_type_name (typeid(int), int_type_name);
	register_type_name (typeid(float), float_type_name);
	register_type_name (typeid(std::string), string_type_name);

	register_type_factory (int_factory, int_type_name);
	register_type_factory (float_factory, float_type_name);
	register_type_factory (string_factory, string_type_name);
}

}
