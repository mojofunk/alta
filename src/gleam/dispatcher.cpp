namespace gleam {

struct Dispatcher::ThreadData {
	Glib::RefPtr<Glib::MainContext> m_context;
};

Dispatcher::Dispatcher(const char* const name)
    : m_name(name)
    , m_quit(false)
    , m_thread()
    , m_thread_data()
{
}

Dispatcher::~Dispatcher()
{
	g_assert(!m_thread);

	m_thread = 0;
}

void Dispatcher::run()
{
	const sigc::slot<void> main_func =
	    sigc::mem_fun(*this, &Dispatcher::thread_main);

	{
		Glib::Mutex::Lock guard(m_iter_mtx);

		m_thread = Glib::Thread::create(main_func, true);

		// wait thread to start
		m_cond.wait(m_iter_mtx);
	}
}

void Dispatcher::quit()
{
	g_assert(m_thread);

	Glib::Mutex::Lock lock(m_iter_mtx);

	m_quit = true;

	// wait for the iteration to complete
	// which can only happen when m_iter_mtx
	// is released in the wait.
	m_cond.wait(m_iter_mtx);

	// free all resources for the thread
	m_thread->join();
	m_thread = 0;
}

Glib::RefPtr<Glib::MainContext> Dispatcher::get_main_context()
{
	return m_thread_data.get()->m_context;
}

void Dispatcher::thread_main()
{
	ThreadData* pdata = new ThreadData;
	m_thread_data.set(pdata);

	pdata->m_context = Glib::MainContext::create();

	/**
	 * This is the chance for inheriting thread classes
	 * attach event sources to the Glib::MainContext.
	 */
	on_run();

	{
		Glib::Mutex::Lock guard(m_iter_mtx);
		m_cond.signal();
	}

	// start the processing loop
	main_loop();

	on_quit();
}

bool Dispatcher::can_run()
{
	Glib::Mutex::Lock guard(m_iter_mtx);

	if (m_quit) {
		m_cond.signal();
		return false;
	}
	return true;
}

void Dispatcher::main_loop()
{
	while (can_run()) {
		get_main_context()->iteration(true);
	}
}

} // namespace gleam
