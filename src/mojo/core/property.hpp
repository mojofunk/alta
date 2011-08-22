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

#ifndef MOJO_PROPERTY
#define MOJO_PROPERTY

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

#endif
