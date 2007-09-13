
#ifndef ARK_PROPERTY_INCLUDED
#define ARK_PROPERTY_INCLUDED

#include <string>
#include <set>

#include <boost/any.hpp>

namespace ark {

using std::string;
using std::set;

class Property
{
	string name;
	boost::any value;
};

typedef set<Property> Properties;

} // namespace ark

#endif
