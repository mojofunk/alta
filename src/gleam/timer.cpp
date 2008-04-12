
#include <gleam/timer.hpp>

namespace gleam {

Timer::Timer (unsigned int interval,
		Glib::RefPtr<Glib::MainContext> main_context)
:
	m_timeout_interval(interval),
	m_main_context(main_context)
{

}

void
Timer::start_timer()
{
	const Glib::RefPtr<Glib::TimeoutSource> timeout_source = Glib::TimeoutSource::create(m_timeout_interval);
	m_timeout_connection = timeout_source->connect(sigc::mem_fun(this, &Timer::timeout_handler));

	// The MainContext takes a reference to the timeout source
	// so the source that was created stays around after the RefPtr
	// goes out of scope.
	timeout_source->attach(m_main_context);
}

void
Timer::stop_timer()
{
	m_timeout_connection.disconnect();
}


bool
Timer::timeout_handler()
{
	return on_timer();
}

} // namespace gleam
