
#ifndef GLEAM_PERIODIC_SIGNALS_INCLUDED
#define GLEAM_PERIODIC_SIGNALS_INCLUDED

#include <libgleam/periodic_signal.hpp>

namespace gleam {

class PeriodicSignals : public sigc::trackable
{
public:

	PeriodicSignals(Glib::RefPtr<Glib::MainContext> main_context = Glib::MainContext::get_default(),
	                int priority = Glib::PRIORITY_DEFAULT,
	                unsigned int slow = 1000,
	                unsigned int fast = 100,
	                unsigned int rapid = 40,
	                unsigned int blink = 240);

	PeriodicSignal& slow() { return m_slow; }
	PeriodicSignal& fast() { return m_fast; }
	PeriodicSignal& rapid() { return m_rapid; }

	sigc::signal<void, bool>& blink();

private:

	PeriodicSignal               m_slow;
	PeriodicSignal               m_fast;
	PeriodicSignal               m_rapid;
	PeriodicSignal               m_blink;
	
	sigc::signal<void, bool>     m_blink_signal;
	sigc::connection             m_blink_connection;

	void on_blink_timeout();
};

} // namespace gleam

#endif // GLEAM_PERIODIC_SIGNALS_INCLUDED
