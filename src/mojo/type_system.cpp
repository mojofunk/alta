
#include <map>
#include <set>

#include <cassert>

#include <mojo/type_system.hpp>

#include <mojo/type.hpp>

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

TypeNameMap* s_type_names = 0;

typedef set<mojo::TypeSPtr> Types;

Types* s_types = 0;

void
register_type_name (const std::type_info& info,
		const std::string& type_name)
{
	s_type_names->insert(std::make_pair (&info, type_name));
}

}

namespace mojo {

void
type_system_init()
{
	assert(!s_type_names);
	assert(!s_types);

	s_type_names = new TypeNameMap;
	s_types = new Types;
}

void
register_type (TypeSPtr type)
{
	register_type_name (type->type_info(), type->type_name());

	s_types->insert(type);
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


boost::any
create_type (const std::string& type_name)
{
	for (Types::const_iterator i = s_types->begin();
			i != s_types->end(); ++i)
	{
		if ((*i)->type_name() == type_name) return (*i)->create();
	}

	return boost::any();
}

}
