#ifndef MOJO_PROPERTY_H
#define MOJO_PROPERTY_H

#include <glib.h>

#include <boost/any.hpp>

#include <string>
#include <map>

namespace mojo {

typedef GQuark PropertyID;

struct Property
{
	/**
	 * Create an invalid property by default
	 */
	Property () : name(0) { }

	Property (const Property& other)
		: name(other.name)
		, value(other.value)
	{ }

	Property (const std::string& name_arg, const boost::any& value_arg)
		: name(g_quark_from_string(name_arg.c_str())), value(value_arg)
	{ }

	Property (const PropertyID& name_arg, const boost::any& value_arg)
		: name(name_arg), value(value_arg)
	{ }

	bool operator ! () const
	{
		return name == 0 || value.empty();
	}

	bool operator< (const Property& other) const
	{
		return name < other.name;
	}

	std::string get_name_string () const
	{
		return g_quark_to_string (name);
	}

	PropertyID         name;
	boost::any         value;
};

} // namespace mojo

#endif // MOJO_PROPERTY_H
