#ifndef MOJO_CORE_TYPE_REGISTRY_H
#define MOJO_CORE_TYPE_REGISTRY_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"

#endif

namespace mojo {

class TypeRegistry {
public:
	void set_type_name(const std::type_info& info, const std::string& type_name)
	{
		m_type_names.insert(std::make_pair(&info, type_name));
	}

	const std::string get_type_name(const std::type_info& info)
	{
		TypeNameMap::const_iterator i = m_type_names.find(&info);

		if (i != m_type_names.end()) {
			return i->second;
		}

		return "unknown";
	}

private:
	struct TypeInfoComp
	    : std::binary_function<std::type_info*, std::type_info*, bool> {
		bool operator()(const std::type_info* lhs, const std::type_info* rhs) const
		{
			return lhs->before(*rhs);
		}
	};

	using TypeNameMap = std::map<const std::type_info*, std::string, TypeInfoComp>;

	TypeNameMap m_type_names;
};

} // namespace mojo

#endif
