#include "application_worker.hpp"

#include "log.hpp"

namespace mojo {

ApplicationWorker::ApplicationWorker ()
{

}

void
ApplicationWorker::call_sync (const function_t& func)
{
	LOG;
	queue (func);
	iteration(true);
}

void
ApplicationWorker::call_async (const function_t& func)
{
	LOG;
	queue (func);
	iteration(false);
}

void
ApplicationWorker::queue (const function_t& func)
{
	{
		Glib::Mutex::Lock guard(m_queue_lock);
		m_queue.push (func);
	}
}

void
ApplicationWorker::do_work ()
{
	LOG;
	process_queue();
}

void
ApplicationWorker::process_queue ()
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
