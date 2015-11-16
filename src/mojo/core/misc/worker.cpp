namespace mojo {

Worker::Worker()
    : m_quit(false)
{
}

Worker::~Worker()
{
}

void Worker::run()
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

void Worker::quit()
{
	std::unique_lock<std::mutex> lock(m_iter_mtx);

	m_quit = true;

	iteration(false);

	// wait for the iteration to complete
	// which can only happen when m_iter_mtx
	// is released in the wait.
	m_cond.wait(lock);
}

bool Worker::can_run()
{
	std::unique_lock<std::mutex> lock(m_iter_mtx);

	if (m_quit) {
		m_cond.notify_one();
		return false;
	}
	return true;
}

void Worker::iteration(bool block)
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

} // namespace mojo
