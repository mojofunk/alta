
#ifndef GLEAM_STANDARD_TIMER
#define GLEAM_STANDARD_TIMER

#include <gleam/timer.hpp>

namespace gleam {

class StandardTimer : public Timer
{
public:

	StandardTimer (unsigned int interval);

	sigc::connection connect (const sigc::slot<void>& slot);

protected:

	virtual bool on_timer();

private:

	sigc::signal<void>                  m_signal;

};

} // namespace gleam

#endif
