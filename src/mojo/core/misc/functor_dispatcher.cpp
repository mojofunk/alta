MOJO_DEBUG_DOMAIN(FUNCTOR_DISPATCHER);

std::shared_ptr<logging::Logger>& FunctorDispatcher::get_logger()
{
	static std::shared_ptr<logging::Logger> logger = logging::make_logger("FunctorDispatcher");
	return logger;
};

FunctorDispatcher::FunctorDispatcher()
{
}

FunctorDispatcher::~FunctorDispatcher()
{
	assert(m_queue.empty());
}

void FunctorDispatcher::call_sync(const function_type& func)
{
	if (m_quit) {
		// This should be some sort of error the caller must guarentee that
		// no more calls functors are queued
		return;
	}
	MOJO_DEBUG(FUNCTOR_DISPATCHER);
	queue(func);
	iteration(true);
}

void FunctorDispatcher::call_async(const function_type& func)
{
	if (m_quit) {
		// This should be some sort of error the caller must guarentee that
		// no more calls functors are queued
		return;
	}
	MOJO_DEBUG(FUNCTOR_DISPATCHER);
	queue(func);
	iteration(false);
}

void FunctorDispatcher::queue(const function_type& func)
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);
	m_queue.push(func);
}

void FunctorDispatcher::do_work()
{
	MOJO_DEBUG(FUNCTOR_DISPATCHER);
	process_queue();
}

void FunctorDispatcher::process_queue()
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);

	while (!m_queue.empty()) {

		function_type func = m_queue.front();
		m_queue.pop();

		// unlock while executing
		lock.unlock();
		MOJO_DEBUG(FUNCTOR_DISPATCHER);
		func();
		lock.lock();
	}
}
