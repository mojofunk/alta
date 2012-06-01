
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
	{
		Glib::Mutex::Lock guard(m_queue_lock);
		m_queue.push (func);
	}
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
