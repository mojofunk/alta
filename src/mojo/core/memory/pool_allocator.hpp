#ifndef MOJO_CORE_MEMORY_POOL_ALLOCATOR_H
#define MOJO_CORE_MEMORY_POOL_ALLOCATOR_H

#ifndef MOJO_AMALGAMATED
#include "mojo/core/config/common_header_includes.hpp"
#include "mojo/core/memory/fixed_size_pool.hpp"
#endif

/**
 * All Pool allocators should be MT safe.
 *
 * A FixedSizePool allocator is guaranteed to be lock-free and wait-free but can
 * fail to allocate if pool is empty.
 *
 * A VariableSizePool allocator is lock-free and wait-free unless the pool is
 * empty in which case more memory will be allocated which may not be
 * wait-free. The pool could also shrink if necessary although that may get
 * complicated.
 *
 * The maximum number of instances in the pool is
 * std::numeric_limits<std::uint16_t>::max() as result of boost::lockfree
 */
namespace mojo {

namespace memory {

template <typename T>
class PoolAllocator {
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	typedef std::uint16_t max_size_type;

public:
	template <typename U>
	struct rebind {
		typedef PoolAllocator<U> other;
	};

public:
	inline explicit PoolAllocator(const uint16_t count)
	    : m_pool(new FixedSizePool(sizeof(T), count))
	{
	}

	inline ~PoolAllocator() {}

	inline explicit PoolAllocator(const PoolAllocator<T>& other)
	    : m_pool(other.m_pool)
	{
	}

#if 0
	template <typename U>
	inline explicit PoolAllocator(const PoolAllocator<U>&)
	{
	}
#endif

	bool empty () { return false; }

	inline pointer address(reference r) { return &r; }
	inline const_pointer address(const_reference r) { return &r; }

	inline pointer allocate(size_type cnt,
	                        typename std::allocator<void>::const_pointer = 0)
	{
		/**
		 * TODO return memory allocated from the head but kept in a number of
		 * stacks/Pools that can be used for various values of cnt.
		 * A stack for cnt == 1
		 * A stack for cnt == size/X
		 */
		return reinterpret_cast<pointer>(::operator new(cnt * sizeof(T)));
	}

	inline void deallocate(pointer p, size_type) { ::operator delete(p); }

	inline size_type max_size() const
	{
		return std::numeric_limits<size_type>::max() / sizeof(T);
	}

	inline void construct(pointer p, const T& t)
	{
		new (p) T(t);
	}

	inline void destroy(pointer p) { p->~T(); }

	inline bool operator==(PoolAllocator const&) { return true; }
	inline bool operator!=(PoolAllocator const& a) { return !operator==(a); }

private:

	std::shared_ptr<FixedSizePool> m_pool;
};

} // namespace memory

} // namespace mojo

#endif // MOJO_CORE_POOL_ALLOCATOR_H
