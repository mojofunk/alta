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

#include <gleam/dispatcher.hpp>

namespace gleam {

struct Dispatcher::ThreadData {
	Glib::RefPtr<Glib::MainContext> m_context;
};

Dispatcher::Dispatcher(const char* const name)
    : m_name(name)
    , m_quit(false)
    , m_thread()
    , m_thread_data()
{
}

Dispatcher::~Dispatcher()
{
	g_assert(!m_thread);

	m_thread = 0;
}

void Dispatcher::run()
{
	const sigc::slot<void> main_func =
	    sigc::mem_fun(*this, &Dispatcher::thread_main);

	{
		Glib::Mutex::Lock guard(m_iter_mtx);

		m_thread = Glib::Thread::create(main_func, true);

		// wait thread to start
		m_cond.wait(m_iter_mtx);
	}
}

void Dispatcher::quit()
{
	g_assert(m_thread);

	Glib::Mutex::Lock lock(m_iter_mtx);

	m_quit = true;

	// wait for the iteration to complete
	// which can only happen when m_iter_mtx
	// is released in the wait.
	m_cond.wait(m_iter_mtx);

	// free all resources for the thread
	m_thread->join();
	m_thread = 0;
}

Glib::RefPtr<Glib::MainContext> Dispatcher::get_main_context()
{
	return m_thread_data.get()->m_context;
}

void Dispatcher::thread_main()
{
	ThreadData* pdata = new ThreadData;
	m_thread_data.set(pdata);

	pdata->m_context = Glib::MainContext::create();

	/**
	 * This is the chance for inheriting thread classes
	 * attach event sources to the Glib::MainContext.
	 */
	on_run();

	{
		Glib::Mutex::Lock guard(m_iter_mtx);
		m_cond.signal();
	}

	// start the processing loop
	main_loop();

	on_quit();
}

bool Dispatcher::can_run()
{
	Glib::Mutex::Lock guard(m_iter_mtx);

	if (m_quit) {
		m_cond.signal();
		return false;
	}
	return true;
}

void Dispatcher::main_loop()
{
	while (can_run()) {
		get_main_context()->iteration(true);
	}
}

} // namespace gleam
