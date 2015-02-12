#include <map>
#include <set>

#include <cassert>

#include "type_system.hpp"
#include "type_factory.hpp"

using std::map;
using std::set;
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

TypeNameMap&
get_type_name_map ()
{
	static TypeNameMap s_type_names;
	return s_type_names;
}

typedef set<mojo::TypeFactorySP> Types;

Types&
get_types ()
{
	static Types s_types;
	return s_types;
}

void
register_type_name (const std::type_info& info,
		const std::string& type_name)
{
	get_type_name_map().insert(std::make_pair (&info, type_name));
}

}

namespace mojo {

void
TypeSystem::register_type (TypeFactorySP type)
{
	register_type_name (type->type_info(), type->type_name());

	get_types().insert(type);
}

const string
TypeSystem::get_type_name (const std::type_info& info)
{
	TypeNameMap::const_iterator i = get_type_name_map().find(&info);
	
	if (i != get_type_name_map().end())
	{
		return i->second;
	}

	return "unknown";
}

boost::any
TypeSystem::create_type (const std::string& type_name)
{
	for (Types::const_iterator i = get_types().begin();
			i != get_types().end(); ++i)
	{
		if ((*i)->type_name() == type_name) return (*i)->create();
	}

	return boost::any();
}

}
