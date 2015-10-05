#ifndef MOJO_CORE_FIXED_SIZE_POOL_H
#define MOJO_CORE_FIXED_SIZE_POOL_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

template <class T>
class FixedSizePool {
public:
	FixedSizePool(const uint16_t size)
	    : m_array(new T[size])
	    , m_size(size)
	    , m_available(size)
	    , m_stack(size)
	{
		for (T* tmp = m_array; tmp < end(); tmp++) {
			bool pushed = m_stack.push(tmp);
			assert(pushed);
		}
	}

	~FixedSizePool()
	{
		assert(m_available == m_size);
		delete[] m_array;
	}

	// return true if allocated by pool
	bool is_from(T* ptr) const { return (ptr >= m_array) && (ptr < end()); }

	uint16_t size() const { return m_size; }

	// not MT safe, just an indication
	uint16_t available() const { return m_available; }

	// not MT safe, just an indication
	bool empty() const { m_available == 0; }

	T* allocate()
	{
		T* instance = nullptr;
		if (m_stack.pop(instance)) {
			m_available--;
		}
		return instance;
	}

	void deallocate(T* ptr)
	{
		if (!is_from(ptr)) {
			assert(true);
			return;
		}
		if (m_stack.push(ptr)) {
			m_available++;
		} else {
			assert(true);
		}
		ptr = nullptr;
	}

private: // methods
	T* end() const { return m_array + m_size; }

private: // data
	typedef boost::lockfree::stack<T*, boost::lockfree::fixed_sized<true>>
	    stack_type;

	T* m_array;
	const uint16_t m_size;
	std::atomic<uint16_t> m_available;
	stack_type m_stack;
};

} // namespace mojo

#endif // MOJO_CORE_FIXED_SIZE_POOL_H
