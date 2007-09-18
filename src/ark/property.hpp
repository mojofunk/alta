
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
public:

	Property (const string& name, const boost::any& value)
		:
			m_name(name),
			m_value(value)
	{ }

	Property (const Property& prop)
		:
			m_name(prop.m_name),
			m_value(prop.m_value)
	{ }

	const string& name() const { return m_name; }

	const boost::any& value() const { return m_value; }

	bool operator<(const Property & rhs) const
	{
		return m_name < rhs.m_name;
	}

private:

	const string m_name;
	const boost::any m_value;

};

typedef set<Property> Properties;

} // namespace ark

#endif
