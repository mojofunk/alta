
#ifndef MOJO_PROPERTIES_INCLUDED
#define MOJO_PROPERTIES_INCLUDED

#include <string>
#include <map>

#include <boost/any.hpp>

namespace mojo {

typedef std::map<std::string, boost::any> Properties;

/**
 * A convenience template function for creating a property pair
 * @param name The property name
 * @param value The property value
 */
template<class NameType, class ValueType>
inline std::pair<NameType, ValueType>
make_property(NameType name, ValueType value)
{
	return std::pair<NameType, ValueType>(name, value);
}

} // namespace mojo

#endif
