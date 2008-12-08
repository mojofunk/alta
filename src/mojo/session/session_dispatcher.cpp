#include "session_dispatcher.hpp"

#include <glibmm/timer.h>

#include <iostream>

namespace mojo {

SessionDispatcher::SessionDispatcher ()
	: ManualDispatcher ("session-dispatcher")
{ }


void
SessionDispatcher::on_run ()
{
	std::cerr << "SD::on_run" << std::endl;

	sigc::slot<void> thread_func;
	thread_func = sigc::mem_fun (*this, &SessionDispatcher::process_queue);

	get_main_context()->signal_idle().connect(
			sigc::bind_return(thread_func, true)
			);

}

void
SessionDispatcher::on_quit ()
{
	std::cerr << "SD::on_quit" << std::endl;
}

void
SessionDispatcher::queue (const function_t& func)
{
	{
		Glib::Mutex::Lock guard(m_queue_lock);
		m_queue.push (func);
	}
	iteration(false);
}


void
SessionDispatcher::process_queue ()
{
	std::cerr << "SD::process_queue" << std::endl;

	for(;;)
	{
		function_t func;

		{
			Glib::Mutex::Lock guard(m_queue_lock);
			func = m_queue.front ();
			if (!func) break;
			m_queue.pop ();
		}
		std::cerr << "SD::process_queue func()" << std::endl;
		func();
	}
}

} // namespace mojo
