
#include <map>

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

}

namespace mojo {

void
type_system_init()
{
	if (!s_type_names)
	{
		s_type_names = new TypeNameMap;
	}
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

}
