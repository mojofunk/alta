#ifndef MOJO_FUNCTOR_DISPATCHER_H
#define MOJO_FUNCTOR_DISPATCHER_H

/**
 * The FunctorDispatcher class accepts worker functions to
 * be called in another thread.
 */
class FunctorDispatcher : public Worker {
public:
	typedef boost::function<void()> function_t;

	FunctorDispatcher();

	~FunctorDispatcher();

	void call_sync(const function_t& func);

	void call_async(const function_t& func);

private:
	virtual void do_work();

	void queue(const function_t& func);

	void process_queue();

	std::queue<function_t> m_queue;
	std::mutex m_queue_mutex;
};

#endif // MOJO_FUNCTOR_DISPATCHER_H
