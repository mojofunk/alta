
#ifndef MOJO_TYPE_NAME_REGISTRY_INCLUDED
#define MOJO_TYPE_NAME_REGISTRY_INCLUDED

#include <map>

#include <ark/type_name_registry.hpp>

namespace mojo {

using std::map;
using std::string;

class TypeNameRegistry : public ark::TypeNameRegistry
{
public:

	TypeNameRegistry();

	virtual const string type_name (const std::type_info& info) const;

private:

	struct TypeInfoComp
		: std::binary_function<std::type_info*, std::type_info*, bool>
	{
		bool operator()(const std::type_info* lhs,
				const std::type_info* rhs) const
		{ return lhs->before(*rhs); }
	};

	typedef map<const std::type_info*, string, TypeInfoComp> TypeNameMap;
	TypeNameMap m_type_names;

};

} // namespace ark

#endif
