
#include <libgleam/semaphore.hpp>

#include "debug.hpp"

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

#ifdef GLEAM_DEBUG_EXTRA
	LOG_GLEAM_DEBUG
		<< "Semaphore AQUIRE"
		<< m_counter.get();
#endif
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

#ifdef GLEAM_DEBUG_EXTRA
	LOG_GLEAM_DEBUG
		<< "Semaphore RELEASE"
		<< m_counter.get();
#endif

	m_cond.signal();
}

} // namespace gleam
