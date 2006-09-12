/*
   Copyright (C) 2006 Tim Mayberry

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA  02110-1301, USA.
*/

#include <iostream> // debug

#include <glib.h>

#include <glibmm/thread.h>

#include <libgleam/thread_map.hpp>

namespace {

const char* const unregistered_thread_name = "Unregistered Thread";

}

namespace gleam {

void
ThreadMap::register_thread (const string& thread_name)
{
	g_assert (!thread_name.empty());
	
	std::pair<string, Glib::Thread*> newpair;
	newpair.first = thread_name;
	newpair.second = Glib::Thread::self();

	{
		Glib::Mutex::Lock guard (m_map_mutex);

		std::pair<ThreadMapType::iterator, bool> success;

		success = m_thread_map.insert(newpair);

		g_assert (success.second);
	}
}

void
ThreadMap::unregister_thread (const string& thread_name)
{
	g_assert(is_thread(thread_name));
	
	{	
		Glib::Mutex::Lock guard (m_map_mutex);

		ThreadMapType::iterator iter;
		
		iter = m_thread_map.find(thread_name);
		
		g_assert (iter != m_thread_map.end());

		m_thread_map.erase(iter);

	}
}

bool
ThreadMap::is_thread (const string& thread_name)
{
	Glib::Mutex::Lock guard (m_map_mutex);

	ThreadMap::ThreadMapType::const_iterator i = m_thread_map.find(thread_name);

	g_assert (i != m_thread_map.end());

	if((*i).second == Glib::Thread::self()) return true;

	return false;
}

bool
ThreadMap::is_not_thread (const string& thread_name)
{
	return !is_thread(thread_name);
}

const string
ThreadMap::current_thread_name ()
{
	ThreadMap::ThreadMapType::const_iterator i;
	string current_thread_name;
	
	{
		Glib::Mutex::Lock guard (m_map_mutex);

		const Glib::Thread* const current_thread = Glib::Thread::self();

		for(i = m_thread_map.begin(); i != m_thread_map.end(); ++i) {
			if((*i).second == current_thread) {
				current_thread_name = (*i).first;
				break;
			}
		}

		//print_thread_map();
		
		if(i == m_thread_map.end()) {
			return unregistered_thread_name;
		}
	}

	return current_thread_name;
}

// m_map_mutex must be held while calling print_thread_map
void
ThreadMap::print_thread_map() const
{
	ThreadMap::ThreadMapType::const_iterator i;
	for(i = m_thread_map.begin(); i != m_thread_map.end(); ++i) {
		std::cerr
			<< "Thread name : " << (*i).first << " "
			<< "address : " << (*i).second
			<< std::endl;
	}
}

} // namespace gleam
