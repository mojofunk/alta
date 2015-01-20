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
			std::unique_lock<std::mutex> lock(m_iter_mtx);

			m_cond.notify_one();
		}
	}
}

void
Worker::quit ()
{
	std::unique_lock<std::mutex> lock(m_iter_mtx);

	m_quit = true;

	iteration (false);

	// wait for the iteration to complete
	// which can only happen when m_iter_mtx
	// is released in the wait.
	m_cond.wait(lock);
}

bool
Worker::can_run()
{
	std::unique_lock<std::mutex> lock(m_iter_mtx);

	if(m_quit)
	{
		m_cond.notify_one();
		return false;
	}
	return true;
}

void
Worker::iteration (bool block)
{
	if(block)
	{
		std::unique_lock<std::mutex> lock(m_iter_mtx);

		//signal worker to run
		m_iter_sema.post();

		// wait for one iteration to complete
		m_cond.wait(lock);
	}
	else
	{
		m_iter_sema.post();
	}
}

} // namespace mojo
