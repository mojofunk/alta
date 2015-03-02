#ifndef GLEAM_TIMER_H
#define GLEAM_TIMER_H

#include <sigc++/signal.h>

#include <glibmm/main.h>

namespace gleam {

/**
 * The Timer class is a wrapper around Glib TimeoutSources
 * The Timer will start automatically when the first connection
 * is made and stop when the last callback is disconnected.
 */
class Timer
{
public:

	Timer (unsigned int interval,
	       const Glib::RefPtr<Glib::MainContext>& main_context);

	unsigned int get_interval () const;

	void set_interval (unsigned int new_interval);

	virtual unsigned int connection_count () const = 0;

protected:

	virtual ~Timer() { }

	void start ();

	void stop ();

	virtual bool on_elapsed () = 0;

private:

	Timer(const Timer&);
	Timer& operator= (const Timer&);

private:

	static gboolean _timeout_handler (void *data);

	bool timeout_handler ();

	GSource*                               m_timeout_source;

	unsigned int                           m_timeout_interval;

	const Glib::RefPtr<Glib::MainContext>  m_main_context;

};

class StandardTimer : public Timer
{
public:

	StandardTimer (unsigned int interval,
	               const Glib::RefPtr<Glib::MainContext>& main_context = Glib::MainContext::get_default());

	sigc::connection connect (const sigc::slot<void>& slot);

	virtual unsigned int connection_count () const
	{ return m_signal.size (); }

protected:

	virtual bool on_elapsed ();

	sigc::signal<void>                     m_signal;

};

class BlinkTimer : public Timer
{
public:

	BlinkTimer (unsigned int interval,
	            const Glib::RefPtr<Glib::MainContext>& main_context = Glib::MainContext::get_default());


	sigc::connection connect (const sigc::slot<void, bool>& slot);

	virtual unsigned int connection_count () const
	{ return m_blink_signal.size (); }

protected:

	virtual bool on_elapsed ();

	sigc::signal<void, bool>               m_blink_signal;

};

} // namespace gleam

#endif // GLEAM_TIMER_H
