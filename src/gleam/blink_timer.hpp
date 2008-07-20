
#ifndef GLEAM_BLINK_TIMER_INCLUDED
#define GLEAM_BLINK_TIMER_INCLUDED

#include <gleam/timer.hpp>

namespace gleam {

class BlinkTimer : public Timer
{
public:

	BlinkTimer (unsigned int interval);

	sigc::connection connect (const sigc::slot<void, bool>& slot);

protected:

	virtual bool on_timer();

private:

	sigc::signal<void, bool> m_blink_signal;

};

} // namespace gleam

#endif