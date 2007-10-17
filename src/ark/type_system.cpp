
#include <map>

#include <ark/type_system.hpp>

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

}

namespace ark {

void
type_system_init()
{
	if (!s_type_names)
	{
		s_type_names = new TypeNameMap;
	}
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

}
