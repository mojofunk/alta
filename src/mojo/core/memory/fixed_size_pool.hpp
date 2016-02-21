#ifndef MOJO_CORE_FIXED_SIZE_POOL_H
#define MOJO_CORE_FIXED_SIZE_POOL_H

class FixedSizePool {
public:
	// Add an alignment argument
	FixedSizePool(const std::size_t size_bytes,
	              const uint32_t count,
	              std::size_t max_expected_threads = 8)
	    : m_block(nullptr)
	    , m_size_bytes(size_bytes)
	    , m_count(count)
	    , m_available(count)
	    , m_queue(count * max_expected_threads)
	{
		m_block = (char*)std::malloc(m_size_bytes * m_count);
		if (!m_block) {
			throw std::bad_alloc();
		}

		for (char* tmp = m_block; tmp < end(); tmp += m_size_bytes) {
			bool queued = m_queue.try_enqueue(tmp);
			assert(queued);
		}
	}

	~FixedSizePool()
	{
		assert(m_available == m_count);
		std::free(m_block);
		m_block = nullptr;
	}

	// return true if allocated by pool
	bool is_from(void* ptr) const
	{
		return ((char*)ptr >= m_block) && ((char*)ptr < end());
	}

	void* allocate(const std::size_t bytes)
	{
		if (bytes > m_size_bytes) {
			return nullptr;
		}

		char* mem = nullptr;
		if (m_queue.try_dequeue(mem)) {
			m_available--;
		} else {
			assert(mem == nullptr);
		}
		return (void*)mem;
	}

	void deallocate(void* ptr)
	{
		if (!is_from(ptr)) {
			assert(true);
			return;
		}
		if (m_queue.try_enqueue((char*)ptr)) {
			m_available++;
		} else {
			assert(true);
		}
		ptr = nullptr;
	}

	bool empty() const { return m_available == 0; }

	uint32_t max_size() const { return m_size_bytes; }

	uint32_t count() const { return m_count; }

	uint32_t available() const { return m_available; }

private: // methods
	char* end() const { return m_block + m_size_bytes * m_count; }

private: // types
	using pool_queue_type = moodycamel::ConcurrentQueue<char*>;

private: // data
	char* m_block;
	const std::size_t m_size_bytes;
	const uint32_t m_count;
	std::atomic<uint32_t> m_available;
	pool_queue_type m_queue;
};

#endif // MOJO_CORE_FIXED_SIZE_POOL_H
