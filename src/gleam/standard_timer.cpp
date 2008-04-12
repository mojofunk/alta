
#include <gleam/standard_timer.hpp>

namespace gleam {

StandardTimer::StandardTimer(unsigned int interval)
:
	Timer(interval)
{

}

sigc::connection
StandardTimer::connect(const sigc::slot<void>& slot)
{
	if(m_signal.size() == 0) { start_timer(); }

	return m_signal.connect(slot);
}

bool
StandardTimer::on_timer()
{
	if(m_signal.size() == 0)
	{
		stop_timer();
		return false;
	}

	m_signal();
	return true;
}

} // namespace gleam
