
#include <map>
#include <cassert>

#include <mojo/type_system.hpp>

using std::map;
using std::string;

namespace {

struct TypeInfoComp
	: std::binary_function<std::type_info*, std::type_info*, bool>
{
	bool operator()(const std::type_info* lhs,
			const std::type_info* rhs) const
	{ return lhs->before(*rhs); }
};

typedef map<const std::type_info*, string, TypeInfoComp> TypeNameMap;

TypeNameMap* s_type_names = 0;

typedef map<string, mojo::type_factory_func_t> TypeFactoryMap;

TypeFactoryMap* s_type_factories = 0;

}

namespace mojo {

void
type_system_init()
{
	assert(!s_type_names);
	assert(!s_type_factories);

	s_type_names = new TypeNameMap;
	s_type_factories = new TypeFactoryMap;
}

void
register_type_name (const std::type_info& info,
		const std::string& type_name)
{
	s_type_names->insert(std::make_pair (&info, type_name));
}

const string
get_type_name (const std::type_info& info)
{
	TypeNameMap::const_iterator i = s_type_names->find(&info);
	
	if (i != s_type_names->end())
	{
		return i->second;
	}

	return "";
}

void
register_type_factory (type_factory_func_t func,
			const std::string& type_name)
{
	s_type_factories->insert(std::make_pair (type_name, func));
}

boost::any
create_type (const std::string& type_name)
{
	TypeFactoryMap::const_iterator i = s_type_factories->find(type_name);
	
	if (i != s_type_factories->end())
	{
		return i->second();
	}

	return boost::any();
}

}
