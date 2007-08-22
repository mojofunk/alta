
#ifndef GLEAM_PERIODIC_SIGNAL_INCLUDED
#define GLEAM_PERIODIC_SIGNAL_INCLUDED

#include <sigc++/trackable.h>
#include <sigc++/signal.h>

#include <glibmm/main.h>

namespace gleam {

class PeriodicSignal : public sigc::trackable
{
    // uncopyable
    PeriodicSignal(const PeriodicSignal&);
    PeriodicSignal& operator= (const PeriodicSignal&);

public:

    PeriodicSignal (unsigned int interval,
	                Glib::RefPtr<Glib::MainContext> main_context = Glib::MainContext::get_default(),
					int priority = Glib::PRIORITY_DEFAULT);

    sigc::signal<void>& signal();

private:

    bool timeout_handler ();

	const unsigned int                  m_timeout_interval;

	Glib::RefPtr<Glib::MainContext>     m_main_context;
	
	const int                           m_priority;

    sigc::signal<void>                  m_signal;

	sigc::connection                    m_timeout_connection;
};

} // namespace gleam

#endif // GLEAM_PERIODIC_SIGNAL_INCLUDED
