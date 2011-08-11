
#ifndef MOJO_PROPERTIES
#define MOJO_PROPERTIES

#include <string>
#include <map>

#include <glib.h>

#include <boost/any.hpp>

namespace mojo {

// use PropertyID in map instead of string
typedef GQuark PropertyID;

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
