
#ifndef MOJO_APPLICATION_WORKER
#define MOJO_APPLICATION_WORKER

#include <queue>

#include <boost/function.hpp>

#include "worker.hpp"

namespace mojo {

/**
 * The ApplicationWorker class accepts worker functions to
 * be called in another thread.
 *
 */
class ApplicationWorker : public Worker
{
public:
	typedef boost::function<void()> function_t;

	ApplicationWorker ();

	void call_sync (const function_t& func);

	void call_async (const function_t& func);

private:

	virtual void do_work ();

	void queue (const function_t& func);

	void process_queue ();

	std::queue<function_t> m_queue;
	Glib::Mutex m_queue_lock;

};

} // namespace mojo

#endif
