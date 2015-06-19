#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/debug/debug.hpp"
#include "mojo/core/misc/functor_dispatcher.hpp"
#endif

MOJO_DEBUG_DOMAIN(FUNCTOR_DISPATCHER);

namespace mojo {

FunctorDispatcher::FunctorDispatcher()
{
}

void FunctorDispatcher::call_sync(const function_t& func)
{
	MOJO_DEBUG(FUNCTOR_DISPATCHER);
	queue(func);
	iteration(true);
}

void FunctorDispatcher::call_async(const function_t& func)
{
	MOJO_DEBUG(FUNCTOR_DISPATCHER);
	queue(func);
	iteration(false);
}

void FunctorDispatcher::queue(const function_t& func)
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);
	m_queue.push(func);
}

void FunctorDispatcher::do_work()
{
	MOJO_DEBUG(FUNCTOR_DISPATCHER);
	process_queue();
}

void FunctorDispatcher::process_queue()
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);

	while (!m_queue.empty()) {

		function_t func = m_queue.front();
		m_queue.pop();

		// unlock while executing
		lock.unlock();
		MOJO_DEBUG(FUNCTOR_DISPATCHER);
		func();
		lock.lock();
	}
}

} // namespace mojo
