RunLoop::RunLoop()
    : m_quit(false)
{
}

RunLoop::~RunLoop()
{
}

void
RunLoop::run()
{
	while (can_run()) {
		m_iter_sema.wait();

		do_work();

		{
			std::unique_lock<std::mutex> lock(m_iter_mtx);

			m_cond.notify_one();
		}
	}
}

void
RunLoop::quit()
{
	if (m_quit) return;

	std::unique_lock<std::mutex> lock(m_iter_mtx);

	m_quit = true;

	iteration(false);

	// wait for the iteration to complete
	// which can only happen when m_iter_mtx
	// is released in the wait.
	m_cond.wait(lock);
}

bool
RunLoop::can_run()
{
	std::unique_lock<std::mutex> lock(m_iter_mtx);

	if (m_quit) {
		m_cond.notify_one();
		return false;
	}
	return true;
}

void
RunLoop::iteration(bool block)
{
	if (block) {
		std::unique_lock<std::mutex> lock(m_iter_mtx);

		// signal worker to run
		m_iter_sema.post();

		// wait for one iteration to complete
		m_cond.wait(lock);
	} else {
		m_iter_sema.post();
	}
}
