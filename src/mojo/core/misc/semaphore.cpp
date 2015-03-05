#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_source_includes.hpp"
#include "mojo/core/misc/semaphore.hpp"
#endif

namespace mojo {

Semaphore::Semaphore (uint32_t initial_val)
	:
		m_counter(initial_val)
{ }

void
Semaphore::wait ()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	while (m_counter < 1) {
		m_cond.wait(lock);
	}

	--m_counter;
}

bool
Semaphore::try_wait ()
{
	std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);
	try {
		if (!lock.try_lock())
		{
			return false;
		}
	} catch (...) {
		return false;
	}
	// lock successful
	while (m_counter < 1) {
		m_cond.wait(lock);
	}

	// should be able to decrement after unlock
	// but it doesn't really matter
	--m_counter;
	return true;
}

void
Semaphore::post ()
{
	++m_counter;
	m_cond.notify_one();
}

} // namespace mojo
