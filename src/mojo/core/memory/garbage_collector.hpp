#ifndef MOJO_CORE_GARBAGE_COLLECTOR_H
#define MOJO_CORE_GARBAGE_COLLECTOR_H

namespace mojo {

class GarbageCollector {
public:
	/**
	 * TODO Using ConcurrentQueue params properly?
	 *
	 * @param max_expected_capacity The maximum expected capacity of elements the
	 * GarbageCollector is expected to hold between calls to run(). If
	 * max_expected_capacity is exceeded more memory my need to be allocated.
	 *
	 * @param max_expected_threads The maximum expected number of threads calling
	 * manage(). If exceeded memory may need to be allocated.
	 */
	GarbageCollector(std::size_t max_expected_capacity,
	                 std::size_t max_expected_threads)
	    : m_max_expected_capacity(max_expected_capacity)
	    , m_max_expected_threads(max_expected_threads)
	    , m_gc_queue(max_expected_capacity * max_expected_threads)
	{
	}

	/**
	 * @param instance_ptr the instance to be managed by the garbage collector
	 *
	 * This method is thread-safe.
	 * This method is lock-free unless the queue is full and memory needs to be
	 * allocated.
	 */
	template <typename T>
	void manage(const std::shared_ptr<T>& instance_ptr)
	{
		if (!instance_ptr) {
			return;
		}

		m_gc_queue.enqueue(instance_ptr);
	}

	/**
	 * @return true if instance was able to be managed without possibly blocking.
	 * @param instance_ptr the instance to be managed by the garbage collector
	 *
	 * This method is thread-safe and lock-free
	 */
	template <typename T>
	bool try_manage(const std::shared_ptr<T>& instance_ptr)
	{
		if (!instance_ptr) {
			return false;
		}

		if (m_gc_queue.try_enqueue(instance_ptr)) {
			return true;
		} else {
			// log it
			return false;
		}
	}

	/**
	 * Run the garbage collection and destroy/drop all instances where the
	 * garbage collector is the only reference holder.
	 *
	 * This method is thread safe but not lock-free(although it should be
	 * possible to make it so)
	 */
	void run();

	/**
	 * TODO Template that takes a std::chrono::duration?
	 */
	void run_max_duration(uint64_t max_approx_microseconds);

	/**
	 * @return The approximate number of instances being managed
	 */
	std::size_t size_approx() { return m_gc_queue.size_approx(); }

private:
	// not sure we will need these around
	std::size_t m_max_expected_capacity;
	std::size_t m_max_expected_threads;

	using gc_queue_type = moodycamel::ConcurrentQueue<std::shared_ptr<void>>;

	gc_queue_type m_gc_queue;

private:
	M_DISALLOW_COPY_AND_ASSIGN(GarbageCollector);
};

} // namespace mojo

#endif // MOJO_CORE_GARBAGE_COLLECTOR_H
