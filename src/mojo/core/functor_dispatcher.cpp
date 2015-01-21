
#include "mojo/core/debug.hpp"

#include "functor_dispatcher.hpp"

namespace mojo {

FunctorDispatcher::FunctorDispatcher ()
{

}

void
FunctorDispatcher::call_sync (const function_t& func)
{
	LOG;
	queue (func);
	iteration(true);
}

void
FunctorDispatcher::call_async (const function_t& func)
{
	LOG;
	queue (func);
	iteration(false);
}

void
FunctorDispatcher::queue (const function_t& func)
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);
	m_queue.push (func);
}

void
FunctorDispatcher::do_work ()
{
	LOG;
	process_queue();
}

void
FunctorDispatcher::process_queue ()
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);

	while (!m_queue.empty()) {

		function_t func = m_queue.front ();
		m_queue.pop ();

		// unlock while executing
		lock.unlock ();
		LOG;
		func();
		lock.lock ();
	}
}

} // namespace mojo
