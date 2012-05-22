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
	Glib::Mutex::Lock guard(m_queue_lock);

	while (!m_queue.empty()) {

		function_t func = m_queue.front ();
		m_queue.pop ();

		// unlock while executing
		m_queue_lock.unlock ();
		LOG;
		func();
		m_queue_lock.lock ();
	}
}

} // namespace mojo
