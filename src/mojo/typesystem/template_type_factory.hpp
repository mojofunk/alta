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

#ifndef MOJO_TEMPLATE_TYPE_FACTORY
#define MOJO_TEMPLATE_TYPE_FACTORY

#include "type_factory.hpp"

namespace mojo {

template <class T>
class TemplateTypeFactory : public TypeFactory
{
public:

	TemplateTypeFactory (const std::string& type_name)
		: m_type_name(type_name) { }

	virtual std::string type_name () const { return m_type_name; }

	virtual boost::any create () const
	{
		return boost::any(new T);
	}

	virtual const std::type_info& type_info () const
	{
		return typeid(T);
	}

private:

	const std::string m_type_name;

};

} // namespace mojo

#endif
