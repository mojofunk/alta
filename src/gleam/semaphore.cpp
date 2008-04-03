
#include <gleam/semaphore.hpp>

namespace gleam {

// These should probably be inline
Semaphore::Semaphore (gint initial_val)
	:
		m_counter(initial_val)
{ }

void
Semaphore::aquire ()
{
	while (m_counter.get() < 1) {
		Glib::Mutex::Lock guard (m_mutex);

		m_cond.wait(m_mutex);

	}

	--m_counter;
}

bool
Semaphore::try_aquire ()
{
	// XXX todo
	return true;
}

void
Semaphore::release ()
{
	++m_counter;

	m_cond.signal();
}

} // namespace gleam
