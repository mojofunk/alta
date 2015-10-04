#ifndef MOJO_CORE_FIXED_SIZE_POOL_H
#define MOJO_CORE_FIXED_SIZE_POOL_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

class FixedSizePool
{
public:
	FixedSizePool(const std::size_t size, const uint32_t count)
		: m_block(nullptr)
		, m_size(size)
		, m_count(count)
		, m_current_count(0)
		, m_stack(count)
	{
		m_block = (char*)std::malloc (m_size * m_count);
		// if(!m_block) throw std::bad_alloc?

		for (char* tmp = m_block; tmp < end(); tmp += m_size) {
			bool pushed = m_stack.push(tmp);
			assert(pushed);
			m_current_count++;
		}
		assert(m_current_count == m_count);
	}

	~FixedSizePool()
	{
		std::free(m_block);
		m_block = nullptr;
		assert(m_current_count == m_count);
	}

	// return true if allocated by pool
	bool is_from(void* ptr)
	{
		return ((char*)ptr >= m_block) && ((char*)ptr < end());
	}

	bool empty() { m_current_count == 0; }

	std::size_t size() { return m_size; }

	std::size_t count() { return m_count; }

	void* allocate(const std::size_t bytes)
	{
		if (bytes > size()) {
			assert(true);
			return nullptr;
		}
		char* mem = nullptr;
		if (m_stack.pop(mem)) {
			m_current_count--;
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
			m_current_count++;
		} else {
			assert(true);
		}
		ptr = nullptr;
	}

private: // methods
	void* end() { return m_block + m_size * m_count; }

private: // data
	typedef boost::lockfree::stack<char*, boost::lockfree::fixed_sized<true>>
	    stack_type;

	char* m_block;
	const std::size_t m_size;
	const uint16_t m_count;
	std::atomic<uint16_t> m_current_count;
	stack_type m_stack;
};

} // namespace mojo

#endif // MOJO_CORE_FIXED_SIZE_POOL_H
