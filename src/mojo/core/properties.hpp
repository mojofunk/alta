/*
   Copyright (C) 2011 Tim Mayberry

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/

#ifndef MOJO_PROPERTIES
#define MOJO_PROPERTIES

#include <string>
#include <set>

#include <glib.h>

#include "property.hpp"

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

#endif
