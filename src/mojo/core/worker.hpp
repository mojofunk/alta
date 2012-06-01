
#ifndef MOJO_API_WORKER
#define MOJO_API_WORKER

#include <glibmm/thread.h>

#include <gleam/gleam.hpp>

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
	
	Glib::Mutex                     m_iter_mtx;

	Glib::Cond                      m_cond;

	bool                            m_quit;

	gleam::Semaphore                m_iter_sema;

};

} // namespace mojo

#endif // MOJO_API_WORKER
