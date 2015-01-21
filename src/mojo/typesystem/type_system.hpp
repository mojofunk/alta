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

#ifndef MOJO_TYPE_SYSTEM
#define MOJO_TYPE_SYSTEM

#include <string>
#include <typeinfo>

#include <boost/any.hpp>

#include "typedefs.hpp"

namespace mojo {

// namespace?
class TypeSystem
{
public:

	static void register_type (TypeFactorySP type);
	
	/**
	 * because std::type_info.name() is not portable between compilers
	 * etc, use a standard mapping of names to types.
	 */
	static const std::string get_type_name (const std::type_info& info);

	/**
	 * Given a portable type name create a specific instance of that
	 * type
	 */
	static boost::any create_type (const std::string& type_name);

};

} // namespace mojo

#endif
