#ifndef MOJO_CORE_MEMORY_POOL_H
#define MOJO_CORE_MEMORY_POOL_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#endif

namespace mojo {

namespace alloc {

template <uint32_t BlockSize, uint32_t Count>
class MemoryPool
{
public:
	typedef std::size_t size_type;

public:
	MemoryPool()
		: m_count(0)
	{
		m_block = (char*)std::malloc (Count * BlockSize);
		// if(!m_block) throw std::bad_alloc?

		for (char* tmp = m_block; tmp < end(); tmp += BlockSize) {
			bool pushed = m_stack.push(tmp);
			assert(pushed);
			m_count++;
		}
		assert(m_count == Count);
	}

	~MemoryPool()
	{
		std::free(m_block);
		m_block = nullptr;
		assert(m_count == Count);
	}

	// return true if allocated by pool
	bool is_from(void* ptr)
	{
		return ((char*)ptr >= m_block) && ((char*)ptr < end());
	}

	bool empty()
	{
		m_count == 0;
	}

	size_type size() { return BlockSize * Count; }

	void* allocate(const size_type bytes)
	{
		assert(bytes <= BlockSize);
		char* mem = nullptr;
		if (m_stack.pop(mem)) {
			m_count--;
		}
		return (void*)mem;
	}

	void deallocate(void* ptr)
	{
		assert(is_from(ptr));
		if (m_stack.push((char*)ptr)) {
			m_count++;
		} else {
			assert(true);
		}
		ptr = nullptr;
	}

	uint32_t get_count() const { return Count; }

	uint32_t get_block_size() const { return BlockSize; }

private:

	void* end() { return m_block + Count*BlockSize; }

private:

	typedef boost::lockfree::stack<char*, boost::lockfree::capacity<Count>> stack_type;

	char* m_block;
	stack_type m_stack;
	std::atomic<uint16_t> m_count;
};

template <typename T, unsigned int Count>
class ObjectMemoryPool : public MemoryPool<sizeof(T), Count> { };

} // namespace alloc

} // namespace mojo

#endif // MOJO_CORE_POOL_ALLOCATOR_H
