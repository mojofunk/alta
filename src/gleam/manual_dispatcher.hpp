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

#ifndef GLEAM_MANUAL_DISPATCHER_INCLUDED
#define GLEAM_MANUAL_DISPATCHER_INCLUDED

#include <gleam/dispatcher.hpp>
#include <gleam/semaphore.hpp>

namespace gleam {

class ManualDispatcher : public Dispatcher
{
public:

	ManualDispatcher(const char* const name);

	/**
	 * Complete one iteration of the main loop. If block is set to
	 * true the calling thread will be blocked until one iteration of 
	 * the threads main loop is completed.
	 */
	void iteration (bool block = false);

	virtual void quit();

protected:

	/**
	 * \see Dispatcher::on_run
	 */
	virtual void on_run() = 0;
	
	/**
	 * \see Dispatcher::on_quit
	 */
	virtual void on_quit() = 0;

private:

	virtual void main_loop ();

	Semaphore		m_iter_sema;
};

} // namespace gleam

#endif // GLEAM_MANUAL_DISPATCHER_INCLUDED
