
#include <boost/preprocessor/stringize.hpp>

#include <mojo/type_name_registry.hpp>

#define MAKE_PAIR(T) std::make_pair(&typeid(T), BOOST_PP_STRINGIZE(T))

namespace mojo {

TypeNameRegistry::TypeNameRegistry()
{
	m_type_names.insert (MAKE_PAIR(string));
	m_type_names.insert (MAKE_PAIR(int));


}

const string
TypeNameRegistry::type_name (const std::type_info& info) const
{
	TypeNameMap::const_iterator i = m_type_names.find(&info);
	
	if (i != m_type_names.end())
	{
		return i->second;
	}

	return "";
}

} // namespace mojo
