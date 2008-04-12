
#include <gleam/blink_timer.hpp>

namespace gleam {

BlinkTimer::BlinkTimer(unsigned int interval)
:
	Timer(interval)
{

}

sigc::connection
BlinkTimer::connect(const sigc::slot<void, bool>& slot)
{
	if(m_blink_signal.size() == 0) { start_timer(); }

	return m_blink_signal.connect(slot);
}

bool
BlinkTimer::on_timer()
{
	static bool blink_on = false;

	if(m_blink_signal.size() == 0)
	{
		stop_timer();
		return false;
	}

	m_blink_signal(blink_on = !blink_on);
	return true;
}

} // namespace gleam
