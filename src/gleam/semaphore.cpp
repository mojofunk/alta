
#include <gleam/semaphore.hpp>

namespace gleam {

Semaphore::Semaphore (gint initial_val)
	:
		m_counter(initial_val)
{ }

void
Semaphore::wait ()
{
	Glib::Mutex::Lock guard (m_mutex);

	while (m_counter.get() < 1) {

		m_cond.wait(m_mutex);

	}

	--m_counter;
}

bool
Semaphore::try_wait ()
{
	if (!m_mutex.trylock())
	{
		return false;
	}
	// lock successful
	while (m_counter.get() < 1) {
		m_cond.wait(m_mutex);

	}

	--m_counter;
	m_mutex.unlock();
	return true;
}

void
Semaphore::post ()
{
	++m_counter;
	m_cond.signal();
}

} // namespace gleam
