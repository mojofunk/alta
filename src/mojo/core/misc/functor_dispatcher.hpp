#ifndef MOJO_FUNCTOR_DISPATCHER_H
#define MOJO_FUNCTOR_DISPATCHER_H

/**
 * The FunctorDispatcher class accepts worker functions to
 * be called in another thread.
 */
class FunctorDispatcher : public Worker {
public:
	typedef std::function<void()> function_type;

	FunctorDispatcher();

	~FunctorDispatcher();

	void call_sync(const function_type& func);

	void call_async(const function_type& func);

private:
	virtual void do_work();

	void queue(const function_type& func);

	void process_queue();

	std::queue<function_type> m_queue;
	std::mutex m_queue_mutex;

public:
	static std::shared_ptr<logging::Logger>& get_logger();
};

#endif // MOJO_FUNCTOR_DISPATCHER_H
