
#ifndef MOJO_SESSION_DISPATCHER
#define MOJO_SESSION_DISPATCHER

#include <queue>

#include <gleam/manual_dispatcher.hpp>
#include <boost/function.hpp>

namespace mojo {

class SessionDispatcher : public gleam::ManualDispatcher
{
public:
	typedef boost::function<void()> function_t;

	SessionDispatcher ();

	void queue (const function_t& func);

private:

	virtual void on_run ();
	virtual void on_quit();

	void process_queue ();

	std::queue<function_t> m_queue;
	Glib::Mutex m_queue_lock;

};

} // namespace mojo

#endif
