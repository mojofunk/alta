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

#include <map>
#include <set>

#include <cassert>

#include "type_system.hpp"
#include "type_factory.hpp"

using std::map;
using std::set;
using std::string;

namespace {

struct TypeInfoComp
	: std::binary_function<std::type_info*, std::type_info*, bool>
{
	bool operator()(const std::type_info* lhs,
			const std::type_info* rhs) const
	{ return lhs->before(*rhs); }
};

typedef map<const std::type_info*, string, TypeInfoComp> TypeNameMap;

TypeNameMap* s_type_names = 0;

typedef set<mojo::TypeFactorySP> Types;

Types* s_types = 0;

void
register_type_name (const std::type_info& info,
		const std::string& type_name)
{
	s_type_names->insert(std::make_pair (&info, type_name));
}

}

namespace mojo {

TypeSystem* TypeSystem::s_type_system = 0;

/* not thread safe */
void
TypeSystem::init ()
{
	assert(!s_type_system);
	s_type_system = new TypeSystem;
}

void
TypeSystem::cleanup ()
{
	assert(s_type_system);
	delete s_type_system;
}

TypeSystem::TypeSystem ()
{
	assert(!s_type_names);
	assert(!s_types);

	s_type_names = new TypeNameMap;
	s_types = new Types;
}

TypeSystem::~TypeSystem ()
{
	delete s_type_names;
	delete s_types;

	s_type_names = 0;
	s_types = 0;
}

void
TypeSystem::register_type (TypeFactorySP type)
{
	register_type_name (type->type_info(), type->type_name());

	s_types->insert(type);
}

const string
TypeSystem::get_type_name (const std::type_info& info)
{
	TypeNameMap::const_iterator i = s_type_names->find(&info);
	
	if (i != s_type_names->end())
	{
		return i->second;
	}

	return "unknown";
}

boost::any
TypeSystem::create_type (const std::string& type_name)
{
	for (Types::const_iterator i = s_types->begin();
			i != s_types->end(); ++i)
	{
		if ((*i)->type_name() == type_name) return (*i)->create();
	}

	return boost::any();
}

}
