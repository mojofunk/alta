namespace gleam {

ManualDispatcher::ManualDispatcher(const char* const name)
    : Dispatcher(name)
{
}

void ManualDispatcher::iteration(bool block)
{
	if (block) {
		Glib::Mutex::Lock guard(m_iter_mtx);

		// signal other thread to run
		m_iter_sema.post();

		// wait for one iteration to complete
		m_cond.wait(m_iter_mtx);
	} else {
		m_iter_sema.post();
	}
}

void ManualDispatcher::quit()
{
	g_assert(m_thread);

	m_quit = true;

	iteration(true);

	// free all resources for the thread
	m_thread->join();
	m_thread = 0;
}

void ManualDispatcher::main_loop()
{
	while (can_run()) {
		m_iter_sema.wait();

		get_main_context()->iteration(true);

		{
			Glib::Mutex::Lock guard(m_iter_mtx);

			m_cond.signal();
		}
	}
}

} // namespace gleam
