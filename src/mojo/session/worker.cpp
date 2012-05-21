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

#include <glib.h>

#include "worker.hpp"

namespace mojo {

Worker::Worker()
       	: m_quit(false)
{

}
	
Worker::~Worker()
{

}
	
void
Worker::run()
{
	while(can_run())
	{
		m_iter_sema.wait();

		do_work();

		{
			Glib::Mutex::Lock guard(m_iter_mtx);

			m_cond.signal();
		}
	}
}

void
Worker::quit ()
{
	Glib::Mutex::Lock lock(m_iter_mtx);

	m_quit = true;

	// wait for the iteration to complete
	// which can only happen when m_iter_mtx
	// is released in the wait.
	m_cond.wait(m_iter_mtx);
}

bool
Worker::can_run()
{
	Glib::Mutex::Lock	guard (m_iter_mtx);

	if(m_quit)
	{
		m_cond.signal();
		return false;
	}
	return true;
}

void
Worker::iteration (bool block)
{
	if(block)
	{
		Glib::Mutex::Lock guard(m_iter_mtx);

		//signal worker to run
		m_iter_sema.post();

		// wait for one iteration to complete
		m_cond.wait(m_iter_mtx);
	}
	else
	{
		m_iter_sema.post();
	}
}

} // namespace mojo
