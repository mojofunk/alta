/*
    Copyright (C) 2007 Tim Mayberry 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <gleam/timer.hpp>

#include "timers.hpp"

using namespace gleam;

namespace {

class Timers
{
public:

	Timers();

	/// signal every second
	StandardTimer& slow() { return m_slow; }
	
	/// signal every tenth of a second
	StandardTimer& fast() { return m_fast; }
	
	/// signal every 40 msec(25 times a second)
	StandardTimer& rapid() { return m_rapid; }

	BlinkTimer& blink() { return m_blink; }

private:

	StandardTimer m_slow;
	StandardTimer m_fast;
	StandardTimer m_rapid;

	BlinkTimer m_blink;
};

Timers* timers = 0;

Timers::Timers()
:
	m_slow(1000),
	m_fast(100),
	m_rapid(40),
	m_blink(240)
{ }

Timers&
get_timers ()
{
	if (!timers)
	{
		timers = new Timers;
	}
	return *timers;
}

} // anon

sigc::connection
slow_timer_connect (const sigc::slot<void>& slot)
{
	return get_timers().slow().connect (slot);
}

sigc::connection
fast_timer_connect (const sigc::slot<void>& slot)
{
	return get_timers().fast().connect (slot);
}

sigc::connection
rapid_timer_connect (const sigc::slot<void>& slot)
{
	return get_timers().rapid().connect (slot);
}

sigc::connection
blink_timer_connect (const sigc::slot<void, bool>& slot)
{ 
	return get_timers().blink().connect (slot);
}

