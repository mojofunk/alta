
#include "dispatcher.hpp"

#include "log.hpp"

namespace ui {

Dispatcher::Dispatcher ()
{

}

void
Dispatcher::run()
{
	{
		m_iter_sema.aquire();

		do_work();

		{
			Glib::Mutex::Lock guard(m_iter_mtx);

			m_cond.signal();
		}
	}
}

void
Dispatcher::iteration (bool block)
{
	if(block)
	{
		Glib::Mutex::Lock guard(m_iter_mtx);

		Glib::signal_idle().connect(sigc::bind_return(sigc::mem_fun(*this, &Dispatcher::run), false));

		//signal to run
		m_iter_sema.release();

		// wait for one iteration to complete
		m_cond.wait(m_iter_mtx);
	}
	else
	{
		Glib::signal_idle().connect(sigc::bind_return(sigc::mem_fun(*this, &Dispatcher::run), false));
		m_iter_sema.release();
	}
}

void
Dispatcher::call_sync (const function_t& func)
{
	LOG;
	queue (func);
	iteration(true);
}

void
Dispatcher::call_async (const function_t& func)
{
	LOG;
	queue (func);
	iteration(false);
}

void
Dispatcher::queue (const function_t& func)
{
	Glib::Mutex::Lock guard(m_queue_lock);
	m_queue.push (func);
}

void
Dispatcher::do_work ()
{
	LOG;
	process_queue();
}

void
Dispatcher::process_queue ()
{
	Glib::Mutex::Lock guard(m_queue_lock);

	while (!m_queue.empty()) {

		function_t func;

		{
			func = m_queue.front ();
			m_queue.pop ();
		}

		m_queue_lock.unlock ();

		if (func) {
			LOG;
			func();
		}

		m_queue_lock.lock ();
	}
}

}
