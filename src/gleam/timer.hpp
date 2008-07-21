
#ifndef GLEAM_TIMER
#define GLEAM_TIMER

#include <sigc++/trackable.h>
#include <sigc++/signal.h>

#include <glibmm/main.h>

namespace gleam {

class Timer : public sigc::trackable
{
	// uncopyable
	Timer(const Timer&);
	Timer& operator= (const Timer&);

public:

	Timer (unsigned int interval,
			Glib::RefPtr<Glib::MainContext> main_context = Glib::MainContext::get_default());

protected:

	virtual ~Timer() { }

	void start_timer();

	void stop_timer();

	virtual bool on_timer() = 0;

private:

	bool timeout_handler ();

	const unsigned int                  m_timeout_interval;

	Glib::RefPtr<Glib::MainContext>     m_main_context;

	sigc::connection                    m_timeout_connection;
};

} // namespace gleam

#endif
