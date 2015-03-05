#ifndef MOJO_API_WORKER_H
#define MOJO_API_WORKER_H

#include <atomic>
#include <mutex>
#include <condition_variable>

#include "mojo/core/semaphore.hpp"

namespace mojo {

class Worker
{
public:

	/**
	 * Create a new Worker, run() must be called to start
	 * the main loop.
	 */
	Worker();
	
	/**
	 * assert that quit() has been called.
	 */
	virtual ~Worker();

	/**
	 * Start the main loop, this will block until quit is called
	 */
	void run();

	void quit();

	void iteration (bool block = false);

protected:

	virtual void do_work () = 0;

	/**
	 * \return true if thread is able to run.
	 */
	bool can_run ();
	
	std::mutex                      m_iter_mtx;

	std::condition_variable         m_cond;

	std::atomic<bool>               m_quit;

	Semaphore                       m_iter_sema;

};

} // namespace mojo

#endif // MOJO_API_WORKER_H