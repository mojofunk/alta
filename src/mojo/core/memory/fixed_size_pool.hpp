#ifndef MOJO_CORE_FIXED_SIZE_POOL_H
#define MOJO_CORE_FIXED_SIZE_POOL_H

namespace mojo {

class FixedSizePool {
public:
	// Add an alignment argument
	FixedSizePool(const std::size_t size_bytes, const uint16_t count)
	    : m_block(nullptr)
	    , m_size_bytes(size_bytes)
	    , m_count(count)
	    , m_available(count)
	    , m_stack(count)
	{
		m_block = (char*)std::malloc(m_size_bytes * m_count);
		if (!m_block) {
			throw std::bad_alloc();
		}

		for (char* tmp = m_block; tmp < end(); tmp += m_size_bytes) {
			bool pushed = m_stack.push(tmp);
			assert(pushed);
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
			assert(true);
			return nullptr;
		}

		char* mem = nullptr;
		if (m_stack.pop(mem)) {
			m_available--;
		}
		return (void*)mem;
	}

	void deallocate(void* ptr)
	{
		if (!is_from(ptr)) {
			assert(true);
			return;
		}
		if (m_stack.push((char*)ptr)) {
			m_available++;
		} else {
			assert(true);
		}
		ptr = nullptr;
	}

	bool empty() const { return m_available == 0; }

	uint16_t max_size() const { return m_size_bytes; }

	uint16_t count() const { return m_count; }

	uint16_t available() const { return m_available; }

private: // methods
	char* end() const { return m_block + m_size_bytes * m_count; }

private: // data
	typedef boost::lockfree::stack<char*, boost::lockfree::fixed_sized<true>>
	    stack_type;

	char* m_block;
	const std::size_t m_size_bytes;
	const uint16_t m_count;
	std::atomic<uint16_t> m_available;
	stack_type m_stack;
};

} // namespace mojo

#endif // MOJO_CORE_FIXED_SIZE_POOL_H
