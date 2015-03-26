#include "timer.hpp"

namespace gleam {

Timer::Timer(unsigned int interval,
             const Glib::RefPtr<Glib::MainContext>& main_context)
    : m_timeout_source(NULL)
    , m_timeout_interval(interval)
    , m_main_context(main_context)
{
}

gboolean Timer::_timeout_handler(void* data)
{
	Timer* const timer = static_cast<Timer*>(data);
	return timer->timeout_handler();
}

unsigned int Timer::get_interval() const { return m_timeout_interval; }

void Timer::set_interval(unsigned int new_interval)
{
	if (new_interval == m_timeout_interval) return;

	stop();
	m_timeout_interval = new_interval;
	start();
}

/**
 * We don't use Glibmm::TimeoutSource::create() here as contrary
 * to the documentation, SignalTimeout::connect and manually
 * adding a TimeoutSource to a GMainContext are not equivalent.
 *
 * SignalTimeout::connect is the equivalent of g_timeout_add in
 * terms off callback timing but TimeoutSource tries to adjust
 * the timeout based on the time elapsed since the last timeout.
 *
 * On Windows with a high frequency timeout(40ms) this causes a
 * small but noticable increase in CPU Usage.
 */
void Timer::start()
{
	if (m_timeout_source) return;

	m_timeout_source = g_timeout_source_new(m_timeout_interval);

#if 0 // support priorites?
	if(priority != G_PRIORITY_DEFAULT)
		g_source_set_priority(source, priority);
#endif

	g_source_set_callback(m_timeout_source, &Timer::_timeout_handler, this, NULL);

	g_source_attach(m_timeout_source, m_main_context->gobj());
	// GMainContext also holds a reference
}

void Timer::stop()
{
	if (m_timeout_source) {
		g_source_destroy(m_timeout_source);
		g_source_unref(m_timeout_source);
		m_timeout_source = NULL;
	}
}

bool Timer::timeout_handler() { return on_elapsed(); }

StandardTimer::StandardTimer(
    unsigned int interval, const Glib::RefPtr<Glib::MainContext>& main_context)
    : Timer(interval, main_context)
{
}

sigc::connection StandardTimer::connect(const sigc::slot<void>& slot)
{
	if (m_signal.size() == 0) {
		start();
	}

	return m_signal.connect(slot);
}

bool StandardTimer::on_elapsed()
{
	if (m_signal.size() == 0) {
		stop();
		return false;
	}

	m_signal();
	return true;
}

BlinkTimer::BlinkTimer(unsigned int interval,
                       const Glib::RefPtr<Glib::MainContext>& main_context)
    : Timer(interval, main_context)
{
}

sigc::connection BlinkTimer::connect(const sigc::slot<void, bool>& slot)
{
	if (m_blink_signal.size() == 0) {
		start();
	}

	return m_blink_signal.connect(slot);
}

bool BlinkTimer::on_elapsed()
{
	static bool blink_on = false;

	if (m_blink_signal.size() == 0) {
		stop();
		return false;
	}

	m_blink_signal(blink_on = !blink_on);
	return true;
}

} // namespace gleam
