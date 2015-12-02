
#ifndef GLEAM_DISPATCHER
#define GLEAM_DISPATCHER

namespace gleam {

class Dispatcher {
public:
	/**
	 * Create a new Dispatcher, run() must be called to actually
	 * create the new thread and start the main loop.
	 */
	Dispatcher(const char* const name);

	/**
	 * assert that quit() has been called.
	 */
	virtual ~Dispatcher();

	/**
	 * Start the main loop of the thread, this will block until
	 * the thread has been created and is in a running state.
	 */
	void run();

	/**
	 * waits for the main loop to quit and joins the thread
	 * and in the process deleting all the thread private data
	 * associated with this thread. You MUST call quit before
	 * deleting a class derived from Dispatcher.
	 */
	virtual void quit();

	const char* const name() { return m_name; }

protected:
	/// name used to identify the dispatcher
	const char* const m_name;

	/**
	 * on_run is called just before entering the main thread
	 * loop, this is the chance to create thread private data
	 * and register handlers with the main context.
	 */
	virtual void on_run() = 0;

	/**
	 * on_quit is called after exiting the main thread loop,
	 * thread private data created in on_run should be automatically
	 * destroyed when the thread exits so this is the last chance
	 * to do something in the context of the the dispatchers thread.
	 */
	virtual void on_quit() = 0;

	/**
	 * \short returns the wrapped Glib::Thread pointer
	 */
	Glib::Thread* threadobj() const { return m_thread; }

	/**
	 * \short access the thread's maincontext
	 */
	Glib::RefPtr<Glib::MainContext> get_main_context();

	virtual void main_loop();

	/**
	 * \return true if thread is able to run.
	 */
	bool can_run();

	Glib::Mutex m_iter_mtx;

	Glib::Cond m_cond;

	bool m_quit;

	Glib::Thread* m_thread;

private:
	void thread_main();

	struct ThreadData;
	Glib::Private<ThreadData> m_thread_data;
};

} // namespace gleam

#endif // GLEAM_DISPATCHER
