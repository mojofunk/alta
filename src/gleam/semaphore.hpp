#ifndef GLEAM_SEMAPHORE_H
#define GLEAM_SEMAPHORE_H

class Semaphore {

	// prevent copying and assignment
	Semaphore(const Semaphore& sema);
	Semaphore& operator=(const Semaphore& sema);

public:
	/**
	 * \param initial_val The initial value of the
	 * semaphore, defaults to 1(binary semaphore)
	 */
	Semaphore(gint initial_val = 1);

	/**
	 * Aquire a "permit" from the semaphore, if one is
	 * available immediately return after reducing the
	 * number of permits by 1. If a permit isn't available
	 * then the thread will be put into a blocked state
	 * until another thread calls release.
	 */
	void wait();

	/**
	 * Try and aquire a permit. This is a non-blocking
	 * operation.
	 * \return true if a permit was able to be aquired, false
	 * if otherwise.
	 */
	bool try_wait();

	/**
	 * Release a permit increasing the number of permits
	 * by one. This is a non-blocking operation.
	 */
	void post();

private:
	atomic_counter m_counter;
	Glib::Cond m_cond;
	Glib::Mutex m_mutex;
};

#endif // GLEAM_SEMAPHORE_H
