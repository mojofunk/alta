
#include <libgleam/periodic_signals.hpp>

namespace gleam {

PeriodicSignals::PeriodicSignals
    (
     Glib::RefPtr<Glib::MainContext> main_context,
     int priority,
     unsigned int slow,
     unsigned int fast,
     unsigned int rapid,
     unsigned int blink
    )
    :
        m_slow(slow, main_context, priority),
        m_fast(fast, main_context, priority),
        m_rapid(rapid, main_context, priority),
        m_blink(blink, main_context, priority)
{

}

sigc::signal<void, bool>&
PeriodicSignals::blink ()
{
	if(m_blink_signal.size() == 0)
	{
		m_blink.signal().connect(sigc::mem_fun(this, &PeriodicSignals::on_blink_timeout));
	}

	return m_blink_signal;
}

void
PeriodicSignals::on_blink_timeout ()
{
    static bool blink_on = false;

    if(m_blink_signal.size() == 0)
    {
        m_blink_connection.disconnect();
        return;
    }

    m_blink_signal(blink_on = !blink_on);
}
    
} // namespace gleam
