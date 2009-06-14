#include "session_worker.hpp"

#include "log.hpp"

namespace mojo {

SessionWorker::SessionWorker ()
{

}

void
SessionWorker::call_sync (const function_t& func)
{
	LOG;
	queue (func);
	iteration(true);
}

void
SessionWorker::call_async (const function_t& func)
{
	LOG;
	queue (func);
	iteration(false);
}

void
SessionWorker::queue (const function_t& func)
{
	{
		Glib::Mutex::Lock guard(m_queue_lock);
		m_queue.push (func);
	}
}

void
SessionWorker::do_work ()
{
	LOG;
	process_queue();
}

void
SessionWorker::process_queue ()
{
	LOG;

	for(;;)
	{
		function_t func;

		{
			Glib::Mutex::Lock guard(m_queue_lock);
			func = m_queue.front ();
			if (!func) break;
			m_queue.pop ();
		}
		LOG;
		func();
	}
}

} // namespace mojo
