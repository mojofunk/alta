#ifndef MOJO_CORE_SEMAPHORE_H
#define MOJO_CORE_SEMAPHORE_H

#ifndef MOJO_CORE_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

class Semaphore {
public:
	// prevent copying and assignment
	Semaphore(const Semaphore& sema) = delete;
	Semaphore& operator=(const Semaphore& sema) = delete;

public:
	/**
	 * \param initial_val The initial value of the semaphore,
	 * defaults to 1(binary semaphore)
	 */
	Semaphore(uint32_t initial_val = 1);

	/**
	 * Aquire a "permit" from the semaphore, if one is
	 * available immediately return after reducing the
	 * number of permits by 1. If a permit isn't available
	 * then the thread will be put into a blocked state
	 * until another thread calls release.
	 */
	void wait();

	/**
	 * Try and aquire a permit. This is a non-blocking operation.
	 *
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
	// counter is atomic so post doesn't need to take lock to post/notify
	std::atomic<uint32_t> m_counter;
	std::condition_variable m_cond;
	std::mutex m_mutex;
};

} // namespace mojo

#endif // MOJO_CORE_SEMAPHORE_H
