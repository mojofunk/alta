#ifndef MOJO_RUN_LOOP_H
#define MOJO_RUN_LOOP_H

class RunLoop
{
public:
	/**
	 * Create a new RunLoop, run() must be called to start
	 * the main loop.
	 */
	RunLoop();

	/**
	 * assert that quit() has been called.
	 */
	virtual ~RunLoop();

	/**
	 * Start the loop, this will block until quit is called
	 */
	void run();

	void quit();

	void iteration(bool block = false);

protected:
	virtual void do_work() = 0;

	/**
	 * \return true if thread is able to run.
	 */
	bool can_run();

	std::mutex m_iter_mtx;

	std::condition_variable m_cond;

	std::atomic<bool> m_quit;

	Semaphore m_iter_sema;
};

#endif // MOJO_RUN_LOOP_H
