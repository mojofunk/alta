#ifndef MOJO_PROPERTIES_H
#define MOJO_PROPERTIES_H

#include <string>
#include <set>

#include <glib.h>

#ifndef MOJO_CORE_AMALGAMATED

#include "property.hpp"

#endif

namespace mojo {

class Properties
{
public:
	typedef std::set<Property>             container_t;
	typedef container_t::iterator          iterator;
	typedef container_t::const_iterator    const_iterator;

	// operator ==

	/**
	bool operator== (const Properties& other) const
	{
		return other.m_properties == m_properties;
	}
	*/
	// iterators

	iterator begin () { return m_properties.begin(); }
	iterator end () { return m_properties.end(); }
	const_iterator end () const { return m_properties.end(); }
	const_iterator begin () const { return m_properties.begin(); }

	template <class ValueType>
	void
	set_property (const PropertyID& name, const ValueType& val)
	{
		m_properties.insert (Property (name, val));
	}

	template <class ValueType>
	void
	set_property (const std::string& name, const ValueType& val)
	{
		m_properties.insert (Property (name, val));
	}

	template <class ValueType>
	void
	get_property (const PropertyID& name, ValueType& val) const
	{
		for (container_t::const_iterator i = m_properties.begin ();
				i != m_properties.end (); ++i)
		{
			if (i->name == name) {
				val = boost::any_cast<ValueType>(i->value);
			}
		}
	}

	template <class ValueType>
	void
	get_property (const std::string& name, ValueType& val) const
	{
		PropertyID id = g_quark_from_string (name.c_str ());

		for (container_t::const_iterator i = m_properties.begin ();
				i != m_properties.end (); ++i)
		{
			if (i->name == id) {
				val = boost::any_cast<ValueType>(i->value);
			}
		}
	}

private:

	container_t m_properties;
};

} // namespace mojo

#endif // MOJO_PROPERTIES_H
