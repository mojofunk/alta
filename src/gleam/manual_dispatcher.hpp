#ifndef GLEAM_MANUAL_DISPATCHER_H
#define GLEAM_MANUAL_DISPATCHER_H

namespace gleam {

class ManualDispatcher : public Dispatcher {
public:
	ManualDispatcher(const char* const name);

	/**
	 * Complete one iteration of the main loop. If block is set to
	 * true the calling thread will be blocked until one iteration of
	 * the threads main loop is completed.
	 */
	void iteration(bool block = false);

	virtual void quit();

protected:
	/**
	 * \see Dispatcher::on_run
	 */
	virtual void on_run() = 0;

	/**
	 * \see Dispatcher::on_quit
	 */
	virtual void on_quit() = 0;

private:
	virtual void main_loop();

	Semaphore m_iter_sema;
};

} // namespace gleam

#endif // GLEAM_MANUAL_DISPATCHER_H
