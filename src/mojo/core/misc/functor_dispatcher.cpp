FunctorDispatcher::FunctorDispatcher()
{
}

FunctorDispatcher::~FunctorDispatcher()
{
	assert(m_queue.empty());
}

void
FunctorDispatcher::call_sync(const function_type& func)
{
	if (m_quit) {
		// This should be some sort of error the caller must guarentee that
		// no more calls functors are queued
		return;
	}
	M_LOG_CALL(core::RunLoop);
	queue(func);
	iteration(true);
}

void
FunctorDispatcher::call_async(const function_type& func)
{
	if (m_quit) {
		// This should be some sort of error the caller must guarentee that
		// no more calls functors are queued
		return;
	}
	M_LOG_CALL(core::RunLoop);
	queue(func);
	iteration(false);
}

void
FunctorDispatcher::queue(const function_type& func)
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);
	m_queue.push(func);
}

void
FunctorDispatcher::do_work()
{
	M_LOG_CALL(core::RunLoop);
	process_queue();
}

void
FunctorDispatcher::process_queue()
{
	std::unique_lock<std::mutex> lock(m_queue_mutex);

	while (!m_queue.empty()) {

		function_type func = m_queue.front();
		m_queue.pop();

		// unlock while executing
		lock.unlock();
		M_LOG_CALL(core::RunLoop);
		func();
		lock.lock();
	}
}
