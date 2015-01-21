
#ifndef MOJO_FUNCTOR_DISPATCHER
#define MOJO_FUNCTOR_DISPATCHER

#include <queue>

#include <boost/function.hpp>

#include "worker.hpp"

namespace mojo {

/**
 * The FunctorDispatcher class accepts worker functions to
 * be called in another thread.
 *
 */
class FunctorDispatcher : public Worker
{
public:
	typedef boost::function<void()> function_t;

	FunctorDispatcher ();

	void call_sync (const function_t& func);

	void call_async (const function_t& func);

private:

	virtual void do_work ();

	void queue (const function_t& func);

	void process_queue ();

	std::queue<function_t> m_queue;
	std::mutex m_queue_mutex;

};

} // namespace mojo

#endif
