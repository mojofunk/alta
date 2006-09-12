
#include <glib.h>

#include <libgleam/manual_dispatcher.hpp>

#include "debug.hpp"

namespace gleam {

ManualDispatcher::ManualDispatcher(const char* const name)
	:
		Dispatcher(name)
{ }

void
ManualDispatcher::iteration (bool block)
{
	if(block)
	{
		Glib::Mutex::Lock guard(m_iter_mtx);

		//signal other thread to run
		m_iter_sema.release();

#ifdef GLEAM_DEBUG_EXTRA
		LOG_GLEAM_DEBUG
			<< "waiting for iteration of ManualDispatcher to finish"
			<< m_name;
#endif
		// wait for one iteration to complete
		m_cond.wait(m_iter_mtx);
	}
	else
	{
		m_iter_sema.release();
	}
}

void
ManualDispatcher::quit ()
{
	g_assert(m_thread);

	m_quit = true;

	iteration(true);

#ifdef GLEAM_DEBUG_EXTRA
	LOG_GLEAM_DEBUG
		<< "Waiting for ManualDispatcher to quit"
		<< m_name;
#endif
	
	// free all resources for the thread
	m_thread->join();
	m_thread = 0;
}

void
ManualDispatcher::main_loop()
{
	while(can_run())
	{
		m_iter_sema.aquire();

#ifdef GLEAM_DEBUG_EXTRA
		LOG_GLEAM_DEBUG << "Iteration of MainContext";
#endif

		get_main_context()->iteration(true);

		{
			Glib::Mutex::Lock guard(m_iter_mtx);

			m_cond.signal();
		}
	}
}

} // namespace gleam
